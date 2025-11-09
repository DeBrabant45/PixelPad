#include "Controllers/CanvasController.hpp"
#include "Events/MouseButtonEvent.hpp"
#include "Events/ToolTypeChangedEvent.hpp"
#include "Events/ColorChangedEvent.hpp"

namespace PixelPad::Presentation
{
	CanvasController::CanvasController(
		PixelPad::Core::Canvas& canvas,
		Application::IDrawService& drawService,
		PixelPad::Infrastructure::EventBus& eventBus,
		PixelPad::Application::CanvasViewport& canvasViewport) :
		m_canvas(canvas),
		m_drawService(drawService),
		m_eventBus(eventBus),
		m_canvasViewport(canvasViewport),
		m_mouseEventToken(),
		m_toolTypeChangeEventToken()
	{
		RegisterEventHandlers();
	}

	void Presentation::CanvasController::RegisterEventHandlers()
	{
		m_mouseEventToken = m_eventBus.Subscribe<PixelPad::Application::MouseButtonEvent>(
			[this](const PixelPad::Application::MouseButtonEvent& evt)
			{
				OnDraw(evt);
			});

		m_toolTypeChangeEventToken = m_eventBus.Subscribe<PixelPad::Application::ToolTypeChangedEvent>(
			[this](const PixelPad::Application::ToolTypeChangedEvent& evt)
			{
				OnToolTypeChange(evt);
			});

		m_toolColorChangeEventToken = m_eventBus.Subscribe<PixelPad::Application::ColorChangedEvent>(
			[this](const PixelPad::Application::ColorChangedEvent& evt)
			{
				OnColorChange(evt);
			});
	}

	void CanvasController::OnDraw(const PixelPad::Application::MouseButtonEvent& mouseButtonEvent)
	{
		m_drawService.ProcessDrawInput(mouseButtonEvent, m_canvasViewport);
	}

	void CanvasController::OnToolTypeChange(const PixelPad::Application::ToolTypeChangedEvent& toolTypeChangedEvent)
	{
		m_drawService.SetTool(toolTypeChangedEvent.NewTool);
	}

	void CanvasController::OnColorChange(const PixelPad::Application::ColorChangedEvent& colorChangedEvent)
	{
		m_drawService.SetColor(colorChangedEvent.NewColor);
	}

	Presentation::CanvasController::~CanvasController()
	{
		UnregisterEventHandlers();
	}

	void Presentation::CanvasController::UnregisterEventHandlers()
	{
		m_eventBus.Unsubscribe<PixelPad::Application::MouseButtonEvent>(m_mouseEventToken);
		m_eventBus.Unsubscribe<PixelPad::Application::ToolTypeChangedEvent>(m_toolTypeChangeEventToken);
	}
}