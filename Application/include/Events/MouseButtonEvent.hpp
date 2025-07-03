#pragma once

#include "Enums/MouseButton.hpp"

namespace PixelPad::Application
{
    struct MouseButtonEvent
    {
        int X;
        int Y;
        bool IsPressed;
        MouseButton Button;
    };
}