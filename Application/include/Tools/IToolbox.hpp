#pragma once

#include "Enums/ToolType.hpp"

namespace PixelPad::Core
{
	class ITool;
}

namespace PixelPad::Application
{
	class IToolbox
	{
	public:
		virtual ~IToolbox() = default;
		virtual PixelPad::Core::ITool& GetTool(ToolType toolType) = 0;
	};
}