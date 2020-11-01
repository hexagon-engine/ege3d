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
    XSetStandardProperties(m_display, m_window, title.c_str(), title.c_str(), None, nullptr, 0, nullptr);

    static const unsigned long eventMask = FocusChangeMask      | ButtonPressMask     |
                                           ButtonReleaseMask    | ButtonMotionMask    |
                                           PointerMotionMask    | KeyPressMask        |
                                           KeyReleaseMask       | StructureNotifyMask |
                                           EnterWindowMask      | LeaveWindowMask     |
                                           VisibilityChangeMask | PropertyChangeMask  |
                                           ExposureMask;

    // enable input
    XSelectInput(m_display, m_window, eventMask);
    XMapWindow(m_display, m_window);

    // setup graphics context
    m_gc = XCreateGC(m_display, m_window, 0, nullptr);
    XSetForeground(m_display, m_gc, settings.getForegroundColor().toIntWithoutAlpha());
    XSetBackground(m_display, m_gc, settings.getBackgroundColor().toIntWithoutAlpha());

    // enable ClientMessage on close
    Atom wmDelete = getOrCreateAtom("WM_DELETE_WINDOW");
    XSetWMProtocols(m_display, m_window, &wmDelete, 1);

    XFlush(m_display);
    return m_window;
}

void XWindowImpl::close()
{
    std::cout << "TODO: XWindowImpl::close()" << std::endl;
    XFreeGC(m_display, m_gc);
    XDestroyWindow(m_display, m_window);
    XCloseDisplay(m_display);
    XFlush(m_display);
}

bool XWindowImpl::dispatchEvent(bool wait)
{
    ASSERT(m_owner->isOpen());
    XEvent event;

    if(wait)
    {
        if(XNextEvent(m_display, &event) < 0)
            return false;
        handleEvent(event);
        return true;
    }
    else
    {
        bool eventOccurred = false;
        while(XCheckIfEvent(m_display, &event, [](Display*, XEvent* event, XPointer ptr)->int {
            return event->xany.window == (::Window)ptr;
        }, (XPointer)m_window))
        {
            eventOccurred = true;
            handleEvent(event);
        }
        return eventOccurred;
    }
}

void XWindowImpl::handleEvent(XEvent& event)
{
    //std::cout << "Event: " << event.type << std::endl;
    switch(event.type)
    {
    case Expose:
        m_needRedraw = true;
        std::cout << "onExpose" << std::endl;
        break;
    case ClientMessage:
        {
            std::cout << "ClientMessage" << std::endl;
            // SFML
            static Atom wmProtocols = getAtom("WM_PROTOCOLS");
            if(event.xclient.message_type == wmProtocols)
            {
                static Atom wmDeleteWindow = getAtom("WM_DELETE_WINDOW");
                if(event.xclient.format == 32 && event.xclient.data.l[0] == (long)wmDeleteWindow)
                {
                    std::cout << "onClose" << std::endl;
                }
            }
        }
        break;
    case DestroyNotify:
        std::cout << "onDestroy" << std::endl;
        break;
    default:
        std::cout << "Invalid event type " << event.type << std::endl;
    }
}

Atom XWindowImpl::getAtom(std::string name)
{
    return XInternAtom(m_display, name.c_str(), False);
}

Atom XWindowImpl::getOrCreateAtom(std::string name)
{
    return XInternAtom(m_display, name.c_str(), True);
}

} // Internal

}
