#pragma once

#include <cstdint>

namespace PixelPad::Core
{
	struct DrawCommand 
	{
		int X;
		int Y;
		uint32_t Color;
		bool IsPressed;

		DrawCommand(int x, int y, uint32_t color, bool isPressed) :
			X(x), 
			Y(y), 
			Color(color), 
			IsPressed(isPressed) { }
	};
}