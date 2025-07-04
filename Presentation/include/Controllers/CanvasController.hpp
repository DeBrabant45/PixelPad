#pragma once

#include "Graphics/Canvas.hpp"
#include "Services/DrawService.hpp"
#include "Services/IDrawService.hpp"
#include "Buses/EventBus.hpp"

namespace PixelPad::Application
{
	struct MouseButtonEvent;
	struct ToolTypeChangedEvent;
}

namespace PixelPad::Presentation
{
	class CanvasController
	{
	public:
		CanvasController(PixelPad::Core::Canvas& canvas, Application::IDrawService& drawService, PixelPad::Infrastructure::EventBus& eventBus);
		~CanvasController();
		void OnDraw(const PixelPad::Application::MouseButtonEvent& mouseButtonEvent);
		void OnToolTypeChange(const PixelPad::Application::ToolTypeChangedEvent& toolTypeChangedEvent);

	private:
		void RegisterEventHandlers();
		void UnregisterEventHandlers();

	private:
		Core::Canvas& m_canvas;
		Application::IDrawService& m_drawService;
		PixelPad::Infrastructure::EventBus& m_eventBus;
		PixelPad::Infrastructure::EventBus::SubscriptionToken m_mouseEventToken;
		PixelPad::Infrastructure::EventBus::SubscriptionToken m_toolTypeChangeEventToken;
	};
}