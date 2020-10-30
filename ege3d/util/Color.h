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

#pragma once

#include <stdint.h>

namespace EGE3d
{

class Color
{
public:
    Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255)
    : r(_r), g(_g), b(_b), a(_a) {}

    explicit Color(uint32_t _int = 0)
    {
        a = _int % 256;
        _int /= 256;
        b = _int % 256;
        _int /= 256;
        g = _int % 256;
        _int /= 256;
        r = _int % 256;
    }

    // TODO: Color from hex, hsv

    uint32_t toInt()
    {
        return a + (b << 8) + (g << 16) + (r << 24);
    }

    uint32_t toIntWithoutAlpha()
    {
        return b + (g << 8) + (r << 16);
    }

    uint8_t r = 0, g = 0, b = 0, a = 255;
};

}
