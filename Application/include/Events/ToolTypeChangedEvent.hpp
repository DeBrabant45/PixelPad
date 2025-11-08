#pragma once

#include "Tools/ToolType.hpp"

namespace PixelPad::Application
{
	struct ToolTypeChangedEvent
	{
		PixelPad::Core::ToolType NewTool;

		ToolTypeChangedEvent(PixelPad::Core::ToolType tool)
		{
			NewTool = tool;
		}
	};
}