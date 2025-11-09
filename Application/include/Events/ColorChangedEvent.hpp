#pragma once

#include "Graphics/Color.hpp"

namespace PixelPad::Application
{
	struct ColorChangedEvent
	{
		PixelPad::Core::Color NewColor;

		ColorChangedEvent(PixelPad::Core::Color color)
		{
			NewColor = color;
		}
	};
}
