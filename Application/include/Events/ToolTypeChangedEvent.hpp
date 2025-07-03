#pragma once

#include "Enums/ToolType.hpp"

namespace PixelPad::Application
{
	struct ToolTypeChangedEvent
	{
		PixelPad::Application::ToolType NewTool;
	};
}