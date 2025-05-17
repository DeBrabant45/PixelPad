#include "Controllers/CanvasController.hpp"

namespace PixelPad::Presentation
{
	CanvasController::CanvasController(
		PixelPad::Core::Canvas& canvas,
		Application::DrawService& drawService) :
		m_canvas(canvas),
		m_drawService(drawService)
	{

	}

	void CanvasController::SetBackgroundColor(int color)
	{
		m_backgroundColor = color;
	}

	void CanvasController::DrawPixel(int x, int y, int color)
	{
		m_drawService.DrawPixel(x, y, color);
	}

	void CanvasController::DrawLine(int x1, int y1, int x2, int y2, int color)
	{
		m_drawService.DrawLine(x1, y1, x2, y2, color);
	}

	void CanvasController::Clear()
	{
		m_drawService.ClearCanvas();
	}

	void CanvasController::Fill()
	{
		m_drawService.FillCanvas(m_backgroundColor);
	}
}