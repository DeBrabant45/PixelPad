#include "Services/DrawService.hpp"
#include "Graphics/CanvasSnapshot.hpp"
#include <iostream>

namespace PixelPad::Application
{
	DrawService::DrawService(PixelPad::Core::Canvas& canvas) :
		m_canvas{ canvas },
		m_canvasSnapshot{ }
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