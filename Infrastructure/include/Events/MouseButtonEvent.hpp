#pragma once

#include "Inputs/MouseButton.hpp"

namespace PixelPad::Infrastructure
{
    struct MouseButtonEvent
    {
        int X;
        int Y;
        bool IsPressed;
        MouseButton Button;
    };
}