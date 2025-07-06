#pragma once

#include "Enums/MouseButton.hpp"

namespace PixelPad::Application
{
    struct MouseButtonEvent
    {
        int X;
        int Y;
        MouseButton Button;
        bool IsPressed;

        MouseButtonEvent(int x, int y, bool isPressed, MouseButton button): 
            X(x), 
            Y(y), 
            IsPressed(isPressed), 
            Button(button)  
        {

		}
    };
}