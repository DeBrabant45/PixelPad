#include "Tools/Toolbox.hpp"
#include "Tools/ToolType.hpp"
#include "Tools/PencilTool.hpp"
#include "Tools/LineTool.hpp"
#include "Tools/EraserTool.hpp"
#include "Tools/FillTool.hpp"
#include "Tools/RectangleTool.hpp"
#include "Tools/EllipseTool.hpp"
#include <stdexcept>

namespace PixelPad::Application
{
	Toolbox::Toolbox(PixelPad::Core::Canvas& canvas)
	{
		m_tools.emplace(PixelPad::Core::ToolType::Pencil, std::make_unique<PixelPad::Core::PencilTool>(canvas));
		m_tools.emplace(PixelPad::Core::ToolType::Line, std::make_unique<PixelPad::Core::LineTool>(canvas));
		m_tools.emplace(PixelPad::Core::ToolType::Fill, std::make_unique<PixelPad::Core::FillTool>(canvas));
		m_tools.emplace(PixelPad::Core::ToolType::Eraser, std::make_unique<PixelPad::Core::EraserTool>(canvas));
		m_tools.emplace(PixelPad::Core::ToolType::Rectangle, std::make_unique<PixelPad::Core::RectangleTool>(canvas));
		m_tools.emplace(PixelPad::Core::ToolType::Ellipse, std::make_unique<PixelPad::Core::EllipseTool>(canvas));
	}

	PixelPad::Core::ITool& Toolbox::GetTool(PixelPad::Core::ToolType toolType)
	{
		auto it = m_tools.find(toolType);
		if (it == m_tools.end() || !it->second)
			throw std::runtime_error("Tool not found");

		return *(it->second);
	}
}