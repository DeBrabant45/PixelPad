#include "Tools/Toolbox.hpp"
#include "Enums/ToolType.hpp"
#include "Tools/PencilTool.hpp"
#include "Tools/LineTool.hpp"
#include "Tools/EraserTool.hpp"
#include "Tools/FillTool.hpp"
#include "Tools/RectangleTool.hpp"
#include "Tools/EllipseTool.hpp"
#include <stdexcept>
#include <iostream>

namespace PixelPad::Application
{
	Toolbox::Toolbox(PixelPad::Core::Canvas& canvas)
	{
		m_tools.emplace(ToolType::Pencil, std::make_unique<PixelPad::Core::PencilTool>(canvas));
		m_tools.emplace(ToolType::Line, std::make_unique<PixelPad::Core::LineTool>(canvas));
		m_tools.emplace(ToolType::Fill, std::make_unique<PixelPad::Core::FillTool>(canvas));
		m_tools.emplace(ToolType::Eraser, std::make_unique<PixelPad::Core::EraserTool>(canvas));
		m_tools.emplace(ToolType::Rectangle, std::make_unique<PixelPad::Core::RectangleTool>(canvas));
		m_tools.emplace(ToolType::Ellipse, std::make_unique<PixelPad::Core::EllipseTool>(canvas));

		std::cout << "Size of Toolbox: " << sizeof(*this) << std::endl; // 32
	}

	PixelPad::Core::ITool& Toolbox::GetTool(ToolType toolType)
	{
		auto it = m_tools.find(toolType);
		if (it == m_tools.end() || !it->second)
			throw std::runtime_error("Tool not found");

		return *(it->second);
	}
}