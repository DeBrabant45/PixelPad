#pragma once

#include "Graphics/Canvas.hpp"
#include "Graphics/IDrawService.hpp"
#include "Buses/EventBus.hpp"
#include "Graphics/CanvasViewport.hpp"

namespace PixelPad::Application
{
	struct MouseButtonEvent;
	struct ToolTypeChangedEvent;
	struct ColorChangedEvent;
}

namespace PixelPad::Presentation
{
	class CanvasController
	{
	public:
		CanvasController(
			PixelPad::Core::Canvas& canvas, 
			Application::IDrawService& drawService, 
			PixelPad::Infrastructure::EventBus& eventBus, 
			Application::CanvasViewport& canvasViewport);
		~CanvasController();
		void OnDraw(const PixelPad::Application::MouseButtonEvent& mouseButtonEvent);

	private:
		void RegisterEventHandlers();
		void UnregisterEventHandlers();
		void OnToolTypeChange(const PixelPad::Application::ToolTypeChangedEvent& toolTypeChangedEvent);
		void OnColorChange(const PixelPad::Application::ColorChangedEvent& colorChangedEvent);

	private:
		Core::Canvas& m_canvas;
		Application::IDrawService& m_drawService;
		PixelPad::Infrastructure::EventBus& m_eventBus;
		PixelPad::Application::CanvasViewport& m_canvasViewport;
		PixelPad::Infrastructure::EventBus::SubscriptionToken m_mouseEventToken;
		PixelPad::Infrastructure::EventBus::SubscriptionToken m_toolTypeChangeEventToken;
		PixelPad::Infrastructure::EventBus::SubscriptionToken m_toolColorChangeEventToken;
	};
}