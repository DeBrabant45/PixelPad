#pragma once

#include "Tools/ToolType.hpp"

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
		virtual PixelPad::Core::ITool& GetTool(PixelPad::Core::ToolType toolType) = 0;
	};
}