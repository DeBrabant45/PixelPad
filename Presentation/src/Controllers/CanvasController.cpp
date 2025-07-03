#include "Controllers/CanvasController.hpp"
#include "Events/MouseButtonEvent.hpp"

namespace PixelPad::Presentation
{
	CanvasController::CanvasController(
		PixelPad::Core::Canvas& canvas,
		Application::IDrawService& drawService,
		PixelPad::Infrastructure::EventBus& eventBus) :
		m_canvas(canvas),
		m_drawService(drawService),
		m_backgroundColor(0xFFFFFFFF),
		m_eventBus(eventBus),
		m_mouseEventToken()
	{
		RegisterEventHandlers();
	}

	void Presentation::CanvasController::RegisterEventHandlers()
	{
		// Sample Draw line event for testing
		m_mouseEventToken = m_eventBus.Subscribe<PixelPad::Application::MouseButtonEvent>(
			[this](const PixelPad::Application::MouseButtonEvent& evt)
			{

				if (m_prevX != -1 && m_prevY != -1)
				{
					DrawLine(m_prevX, m_prevY, evt.X, evt.Y, 0xFF000000);
				}

				m_prevX = evt.X;
				m_prevY = evt.Y;
			});

		// We need to take in an input 1, 2, 3 and this will determine the drawe type the user wants to use
		// We do not want to call individual draw methods 
		// Need to detemine if we want to uses a DTO to convert the mouse event to the Application layer
		// Can converting one struct to another cause waste of memory?
	}

	Presentation::CanvasController::~CanvasController()
	{
		UnregisterEventHandlers();
	}

	void Presentation::CanvasController::UnregisterEventHandlers()
	{
		m_eventBus.Unsubscribe<PixelPad::Application::MouseButtonEvent>(m_mouseEventToken);
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

	void Presentation::CanvasController::Resize(int width, int height)
	{
		m_drawService.ResizeCanvas(width, height);
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