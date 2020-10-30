/*
    EGE3d - 3D rendering engine for Hexagon

    Copyright (c) 2020 Hexagon Engine

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "XWindowImpl.h"

#include <ege3d/window/Window.h>
#include <iostream>
#include <unistd.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

namespace EGE3d
{

namespace Internal
{

std::unique_ptr<WindowImpl> WindowImpl::make(Window* window)
{
    ASSERT(window);
    return std::make_unique<XWindowImpl>(window);
}

// XWindowImpl
WindowHandle XWindowImpl::create(size_t sx, size_t sy, std::string title, WindowSettings settings)
{
    char* displayName = getenv("DISPLAY");
    if(!displayName)
    {
        std::cerr << "DISPLAY environment variable not set!" << std::endl;
        return 0;
    }
    m_display = XOpenDisplay(displayName);
    if(!m_display)
    {
        std::cerr << "Failed to open display!" << std::endl;
        return 0;
    }
    m_screen = DefaultScreen(m_display);

    m_window = XCreateSimpleWindow(m_display,
                                   RootWindow(m_display, m_screen),
                                   0,
                                   0,
                                   sx,
                                   sy,
                                   1,
                                   settings.getForegroundColor().toIntWithoutAlpha(),
                                   settings.getBackgroundColor().toIntWithoutAlpha());

    // set title
    if(XSetStandardProperties(m_display, m_window, title.c_str(), title.c_str(), None, nullptr, 0, nullptr) < 0)
    {
        std::cerr << "XSetStandardProperties failed" << std::endl;
        return 0;
    }

    // enable input
    if(XSelectInput(m_display, m_window, ExposureMask | ButtonPressMask | KeyPressMask) < 0)
    {
        std::cerr << "XSelectInput failed" << std::endl;
        return 0;
    }

    if(XMapWindow(m_display, m_window) < 0)
    {
        std::cerr << "XMapWindow failed" << std::endl;
        return 0;
    }

    // setup graphics context
    m_gc = XCreateGC(m_display, m_window, 0, nullptr);

    if(XSetForeground(m_display, m_gc, settings.getForegroundColor().toIntWithoutAlpha()) < 0)
    {
        std::cerr << "XSetForeground failed" << std::endl;
        return 0;
    }

    if(XSetBackground(m_display, m_gc, settings.getBackgroundColor().toIntWithoutAlpha()) < 0)
    {
        std::cerr << "XSetBackground failed" << std::endl;
        return 0;
    }

    return m_window;
}

void XWindowImpl::close()
{
    std::cout << "TODO: XWindowImpl::close()" << std::endl;
    XFreeGC(m_display, m_gc);
    XDestroyWindow(m_display, m_window);
    XCloseDisplay(m_display);
}

void XWindowImpl::dispatchEvents()
{
    ASSERT(m_owner->isOpen());
    XEvent event;
    do
    {
        XNextEvent(m_display, &event);
        switch(event.type)
        {
        case Expose:
            m_needRedraw = true;
            break;
        }
    } while(XPending(m_display));

    if(m_needRedraw)
        std::cout << "need redraw" << std::endl;
}

} // Internal

}
