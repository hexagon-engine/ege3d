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

#include <ege3d/window/Keyboard.h>
#include <ege3d/window/Window.h>
#include <iomanip>
#include <iostream>
#include <unistd.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

namespace EGE3d
{

namespace Internal
{

Keyboard::Key xToEGE(KeySym xkey)
{
    switch(xkey)
    {
    case XK_Escape: return Keyboard::Key::Escape;
    case XK_F1: return Keyboard::Key::F1;
    case XK_F2: return Keyboard::Key::F2;
    case XK_F3: return Keyboard::Key::F3;
    case XK_F4: return Keyboard::Key::F4;
    case XK_F5: return Keyboard::Key::F5;
    case XK_F6: return Keyboard::Key::F6;
    case XK_F7: return Keyboard::Key::F7;
    case XK_F8: return Keyboard::Key::F8;
    case XK_F9: return Keyboard::Key::F9;
    case XK_F10: return Keyboard::Key::F10;
    case XK_F11: return Keyboard::Key::F11;
    case XK_F12: return Keyboard::Key::F12;
    case XK_Insert: return Keyboard::Key::Insert;
    case XK_Delete: return Keyboard::Key::Delete;
    case XK_Home: return Keyboard::Key::Home;
    case XK_End: return Keyboard::Key::End;
    case XK_Page_Up: return Keyboard::Key::PageUp;
    case XK_Page_Down: return Keyboard::Key::PageDown;
    case XK_grave: return Keyboard::Key::Grave;
    case XK_1: return Keyboard::Key::N1;
    case XK_2: return Keyboard::Key::N2;
    case XK_3: return Keyboard::Key::N3;
    case XK_4: return Keyboard::Key::N4;
    case XK_5: return Keyboard::Key::N5;
    case XK_6: return Keyboard::Key::N6;
    case XK_7: return Keyboard::Key::N7;
    case XK_8: return Keyboard::Key::N8;
    case XK_9: return Keyboard::Key::N9;
    case XK_0: return Keyboard::Key::N0;
    case XK_minus: return Keyboard::Key::NMinus;
    case XK_equal: return Keyboard::Key::Equal;
    case XK_BackSpace: return Keyboard::Key::Backspace;
    case XK_Num_Lock: return Keyboard::Key::NumLock;
    case XK_KP_Divide: return Keyboard::Key::NumDivide;
    case XK_KP_Multiply: return Keyboard::Key::NumMultiply;
    case XK_KP_Subtract: return Keyboard::Key::NumSubtract;
    case XK_Tab: return Keyboard::Key::Tab;
    case XK_q: return Keyboard::Key::Q;
    case XK_w: return Keyboard::Key::W;
    case XK_e: return Keyboard::Key::E;
    case XK_r: return Keyboard::Key::R;
    case XK_t: return Keyboard::Key::T;
    case XK_y: return Keyboard::Key::Y;
    case XK_u: return Keyboard::Key::U;
    case XK_i: return Keyboard::Key::I;
    case XK_o: return Keyboard::Key::O;
    case XK_p: return Keyboard::Key::P;
    case XK_bracketleft: return Keyboard::Key::LeftBracket;
    case XK_bracketright: return Keyboard::Key::RightBracket;
    case XK_Return: return Keyboard::Key::Enter;
    case XK_KP_7: return Keyboard::Key::Num7;
    case XK_KP_Home: return Keyboard::Key::Num7;
    case XK_KP_8: return Keyboard::Key::Num8;
    case XK_KP_Up: return Keyboard::Key::Num8;
    case XK_KP_9: return Keyboard::Key::Num9;
    case XK_KP_Page_Up: return Keyboard::Key::Num9;
    case XK_KP_Add: return Keyboard::Key::NumAdd;
    case XK_Caps_Lock: return Keyboard::Key::CapsLock;
    case XK_a: return Keyboard::Key::A;
    case XK_s: return Keyboard::Key::S;
    case XK_d: return Keyboard::Key::D;
    case XK_f: return Keyboard::Key::F;
    case XK_g: return Keyboard::Key::G;
    case XK_h: return Keyboard::Key::H;
    case XK_j: return Keyboard::Key::J;
    case XK_k: return Keyboard::Key::K;
    case XK_l: return Keyboard::Key::L;
    case XK_semicolon: return Keyboard::Key::Semicolon;
    case XK_apostrophe: return Keyboard::Key::Apostrophe;
    case XK_backslash: return Keyboard::Key::Backslash;
    case XK_KP_4: return Keyboard::Key::Num4;
    case XK_KP_Left: return Keyboard::Key::Num4;
    case XK_KP_5: return Keyboard::Key::Num5;
    case XK_KP_6: return Keyboard::Key::Num6;
    case XK_KP_Right: return Keyboard::Key::Num6;
    case XK_Shift_L: return Keyboard::Key::LShift;
    case XK_z: return Keyboard::Key::Z;
    case XK_x: return Keyboard::Key::X;
    case XK_c: return Keyboard::Key::C;
    case XK_v: return Keyboard::Key::V;
    case XK_b: return Keyboard::Key::B;
    case XK_n: return Keyboard::Key::N;
    case XK_m: return Keyboard::Key::M;
    case XK_comma: return Keyboard::Key::Comma;
    case XK_period: return Keyboard::Key::Period;
    case XK_slash: return Keyboard::Key::Slash;
    case XK_Shift_R: return Keyboard::Key::RShift;
    case XK_KP_1: return Keyboard::Key::Num1;
    case XK_KP_End: return Keyboard::Key::Num1;
    case XK_KP_2: return Keyboard::Key::Num2;
    case XK_KP_Down: return Keyboard::Key::Num2;
    case XK_KP_3: return Keyboard::Key::Num3;
    case XK_KP_Page_Down: return Keyboard::Key::Num3;
    case XK_KP_Enter: return Keyboard::Key::NumEnter;
    case XK_Control_L: return Keyboard::Key::LCtrl;
    case XK_Super_L: return Keyboard::Key::LSuper;
    case XK_Super_R: return Keyboard::Key::RSuper;
    case XK_Alt_L: return Keyboard::Key::Alt;
    case XK_space: return Keyboard::Key::Space;
    case XK_Alt_R: return Keyboard::Key::AltGr;
    case XK_Control_R: return Keyboard::Key::RCtrl;
    case XK_Left: return Keyboard::Key::Left;
    case XK_Up: return Keyboard::Key::Up;
    case XK_Down: return Keyboard::Key::Down;
    case XK_Right: return Keyboard::Key::Right;
    case XK_KP_0: return Keyboard::Key::Num0;
    case XK_KP_Insert: return Keyboard::Key::Num0;
    case XK_KP_Decimal: return Keyboard::Key::NumPeriod;
    case XK_KP_Delete: return Keyboard::Key::NumPeriod;
    default:
        return Keyboard::Key::Invalid;
    }
}

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
        } break;
    case DestroyNotify:
        std::cout << "onDestroy" << std::endl;
        break;
    case MotionNotify:
        {
            int x = event.xmotion.x;
            int y = event.xmotion.y;
            std::cout << "onMouseMove x=" << x << " y=" << y << std::endl;
        } break;
    case ButtonPress:
        {
            int button = event.xbutton.button;
            if(button == 4) // wheel up
            {
                std::cout << "onMouseWheel d=" << 1 << std::endl;
            }
            else if(button == 5) // wheel down
            {
                std::cout << "onMouseWheel d=" << -1 << std::endl;
            }
            else
            {
                std::cout << "onMouseButtonPress b=" << button << std::endl;
            }
        } break;
    case ButtonRelease:
        {
            int button = event.xbutton.button;
            if(button == 4 || button == 5) // wheel up/down
            {
                // ignore
            }
            else
            {
                std::cout << "onMouseButtonRelease b=" << button << std::endl;
            }
        } break;
    case KeyPress:
        {
            int key = event.xkey.keycode;
            bool alt = event.xkey.state & Mod1Mask;
            bool control = event.xkey.state & ControlMask;
            bool shift = event.xkey.state & ShiftMask;
            bool super = event.xkey.state & Mod4Mask;

            // SFML
            Keyboard::Key egeKey;
            for(size_t s = 0; s < 4; s++)
            {
                egeKey = xToEGE(XLookupKeysym(&event.xkey, s));
                if(egeKey != Keyboard::Key::Invalid)
                    break;
            }
            std::cout << "onKeyPress k=" << (int)egeKey << " a=" << alt << " c=" << control << " s=" << shift << " u=" << super << std::endl;

            // SFML
            if(!XFilterEvent(&event, None))
            {
                static XComposeStatus status;

                // TODO: it should be dynamic in some way
                char keyBuffer[16];
                if(XLookupString(&event.xkey, keyBuffer, sizeof(keyBuffer), nullptr, &status))
                {
                    std::cout << "onTextEnter " << "str='" << keyBuffer[0] << "'" << std::endl;
                }
            }
        } break;
    case KeyRelease:
        {
            KeySym key = event.xkey.keycode;
            bool alt = event.xkey.state & Mod1Mask;
            bool control = event.xkey.state & ControlMask;
            bool shift = event.xkey.state & ShiftMask;
            bool super = event.xkey.state & Mod4Mask;

            // SFML
            Keyboard::Key egeKey;
            for(size_t s = 0; s < 4; s++)
            {
                egeKey = xToEGE(XLookupKeysym(&event.xkey, s));
                if(egeKey != Keyboard::Key::Invalid)
                    break;
            }

            std::cout << "onKeyRelease k=" << (int)egeKey << " a=" << alt << " c=" << control << " s=" << shift << " u=" << super << std::endl;
        } break;
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
