#include "Graphics/DrawService.hpp"
#include "Graphics/CanvasSnapshot.hpp"
#include "Events/MouseButtonEvent.hpp"
#include "Tools/DrawCommand.hpp"
#include "Enums/ToolType.hpp"

#include <iostream>

namespace PixelPad::Application
{
	DrawService::DrawService(PixelPad::Core::Canvas& canvas, PixelPad::Application::IToolbox& toolbox) :
		m_canvas{ canvas },
		m_toolbox{ toolbox },
		m_currentTool{ &m_toolbox.GetTool(ToolType::Pencil) },
		m_canvasSnapshot{ }
	{
		std::cout << "Size of DrawService: " << sizeof(*this) << std::endl; // 40
	}

	// ToDo: Add unit tests
	void DrawService::SelectTool(const ToolType& toolType)
	{
		if (m_currentTool)
		{
			m_currentTool->Reset();
		}

		m_currentTool = &m_toolbox.GetTool(toolType);
	}

	// ToDo: Add unit tests
	void DrawService::ProcessDrawInput(const PixelPad::Application::MouseButtonEvent& mouseButtonEvent)
	{
		// ToDo: Look into adding radius
		PixelPad::Core::DrawCommand command
		{
			mouseButtonEvent.X,
			mouseButtonEvent.Y,
			0xFF000000, // ToDo: Replace with actual color logic
			mouseButtonEvent.IsPressed
		};

		m_currentTool->Draw(command);
	}

	void DrawService::ClearCanvas()
	{
		m_canvas.Clear();
	}

	void DrawService::ResizeCanvas(int width, int height)
	{
		m_canvas.Resize(width, height);
	}

	std::pair<int, int> DrawService::GetCanvasSize() const
	{
		return std::make_pair(m_canvas.GetWidth(), m_canvas.GetHeight());
	}

	void DrawService::SaveCanvasState()
	{
		m_canvasSnapshot = std::make_unique<PixelPad::Core::CanvasSnapshot>(
			m_canvas.GetWidth(),
			m_canvas.GetHeight(),
			m_canvas.GetPixels()
		);
	}

	void DrawService::LoadCanvasState()
	{
		if (!m_canvasSnapshot) 
			return;

		m_canvasSnapshot->ApplyTo(m_canvas);
	}
}