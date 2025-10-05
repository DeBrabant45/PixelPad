#pragma once

namespace PixelPad::Core
{
	struct Transform
	{
		int X;
		int Y;
		int Z;
		int Width;
		int Height;

		Transform(int x = 0, int y = 0, int z = 0, int width = 0, int height = 0)
			: X(x), Y(y), Z(z) ,Width(width), Height(height)
		{

		}
	};
}
