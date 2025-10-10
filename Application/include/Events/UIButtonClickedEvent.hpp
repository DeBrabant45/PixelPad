#pragma once

#include "Graphics/IUIButton.hpp"

namespace PixelPad::Application
{
	struct UIButtonClickedEvent
	{
		PixelPad::Application::ClickResult ClickResult;
	};
}