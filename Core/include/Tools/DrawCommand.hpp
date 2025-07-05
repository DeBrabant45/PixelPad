#pragma once

namespace PixelPad::Core
{
	struct DrawCommand 
	{
		int X;
		int Y;
		unsigned int Color;
		bool IsPressed;

		DrawCommand(int x, int y, unsigned int color, bool isPressed) : 
			X(x), 
			Y(y), 
			Color(color), 
			IsPressed(isPressed) { }
	};
}