#include "Services/DrawService.hpp"
#include "Graphics/CanvasSnapshot.hpp"
#include "Events/MouseButtonEvent.hpp"

#include <iostream>

namespace PixelPad::Application
{
	DrawService::DrawService(PixelPad::Core::Canvas& canvas) :
		m_canvas{ canvas },
		m_canvasSnapshot{ },
		m_currentToolType{ ToolType::Pencil },
		m_lastXCoordinate{ -1 },
		m_lastYCoordinate{ -1 }
	{

	}

	void DrawService::DrawPixel(int x, int y, int color)
	{
		m_canvas.DrawPixel(x, y, color);
	}

	void DrawService::DrawLine(int startX, int startY, int endX, int endY, int color)
	{
		m_canvas.DrawLine(startX, startY, endX, endY, color);
	}

	void DrawService::ResizeCanvas(int width, int height)
	{
		m_canvas.Resize(width, height);
	}

	void DrawService::FillCanvas(int color)
	{
		m_canvas.Fill(color);
	}

	void DrawService::ClearCanvas()
	{
		m_canvas.Clear();
	}

	std::pair<int, int> DrawService::GetCanvasSize() const
	{
		return std::make_pair(m_canvas.GetWidth(), m_canvas.GetHeight());
	}

	int DrawService::GetPixel(int x, int y) const
	{
		return m_canvas.GetPixel(x, y);
	}

	void DrawService::SetToolType(const ToolType& toolType)
	{
		m_currentToolType = toolType;
		ResetLastCoordinates();

	}

	void DrawService::ResetLastCoordinates()
	{
		m_lastXCoordinate = -1;
		m_lastYCoordinate = -1;
	}

	void DrawService::ProcessDrawInput(const PixelPad::Application::MouseButtonEvent& mouseButtonEvent)
	{
		switch (m_currentToolType)
		{
		case PixelPad::Application::ToolType::None:
			break;
		case PixelPad::Application::ToolType::Pencil:
			DrawWithPencil(mouseButtonEvent);
			break;
		case PixelPad::Application::ToolType::Line:
			DrawWithLineTool(mouseButtonEvent);
			break;
		case PixelPad::Application::ToolType::Fill:
			break;
		case PixelPad::Application::ToolType::Eraser:
			break;
		default:
			break;
		}
	}

	void DrawService::DrawWithPencil(const MouseButtonEvent& mouseButtonEvent)
	{
		if (m_currentToolType != ToolType::Pencil)
			return;

		if (mouseButtonEvent.IsPressed)
		{
			if (m_lastXCoordinate >= 0 && m_lastYCoordinate >= 0)
			{
				DrawLine(m_lastXCoordinate, m_lastYCoordinate, mouseButtonEvent.X, mouseButtonEvent.Y, 0xFF000000);
			}
			else
			{
				DrawPixel(mouseButtonEvent.X, mouseButtonEvent.Y, 0xFF000000);
			}
			m_lastXCoordinate = mouseButtonEvent.X;
			m_lastYCoordinate = mouseButtonEvent.Y;
		}
		else
		{
			ResetLastCoordinates();
		}
	}

	void DrawService::DrawWithLineTool(const MouseButtonEvent& mouseButtonEvent)
	{
		if (m_currentToolType != ToolType::Line)
			return;

		if (m_lastXCoordinate < 0 || m_lastYCoordinate < 0)
		{
			m_lastXCoordinate = mouseButtonEvent.X;
			m_lastYCoordinate = mouseButtonEvent.Y;
		}

		if (!mouseButtonEvent.IsPressed)
		{
			DrawLine(m_lastXCoordinate, m_lastYCoordinate, mouseButtonEvent.X, mouseButtonEvent.Y, 0xFF000000);
			m_lastXCoordinate = mouseButtonEvent.X;
			m_lastYCoordinate = mouseButtonEvent.Y;
		}
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