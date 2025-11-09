#pragma once

#include "Tools/IToolbox.hpp"
#include "Tools/ITool.hpp"
#include "Graphics/Canvas.hpp"
#include "Tools/ToolType.hpp"

#include <map>
#include <memory>

namespace PixelPad::Application
{
	class Toolbox : public IToolbox
	{
	public:
		Toolbox(PixelPad::Core::Canvas& canvas);
		virtual PixelPad::Core::ITool& GetTool(PixelPad::Core::ToolType toolType) override;

	private:
		std::map<PixelPad::Core::ToolType, std::unique_ptr<PixelPad::Core::ITool>> m_tools;
	};
}