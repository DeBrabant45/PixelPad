#include "Services/DrawService.hpp"
#include <iostream>

namespace Application
{
	DrawService::DrawService(Core::CanvasModel& canvasModel) :
		m_canvasModel{ canvasModel }
	{

	}

	void DrawService::DrawPixel(int x, int y, int color)
	{
		m_canvasModel.DrawPixel(x, y, color);
	}

	void DrawService::DrawLine(int startX, int startY, int endX, int endY, int color)
	{
		m_canvasModel.DrawLine(startX, startY, endX, endY, color);
	}

	void DrawService::ResizeCanvas(int width, int height)
	{
		m_canvasModel.Resize(width, height);
	}

	void DrawService::FillCanvas(int color)
	{
		m_canvasModel.Fill(color);
	}

	void DrawService::ClearCanvas()
	{
		m_canvasModel.Clear();
	}

	std::pair<int, int> DrawService::GetCanvasSize() const
	{
		return std::make_pair(m_canvasModel.GetWidth(), m_canvasModel.GetHeight());
	}

	int DrawService::GetPixel(int x, int y) const
	{
		return m_canvasModel.GetPixel(x, y);
	}

	void DrawService::SaveCanvasState()
	{

	}

	void DrawService::LoadCanvasState()
	{

	}
}