#pragma once

#include "Buses/EventBus.hpp"

namespace PixelPad::Application
{
	class IWindow;
}

namespace PixelPad::Presentation
{
	class WindowController
	{
	public:
		WindowController(PixelPad::Application::IWindow& window, PixelPad::Infrastructure::EventBus& m_eventBus);
		~WindowController();
		void Resize(int newWidth, int newHeight);
		void Close();
		bool IsOpen() const;

	private:
		void RegisterEventHandlers();
		void UnregisterEventHandlers();

	private:
		PixelPad::Infrastructure::EventBus& m_eventBus;
		PixelPad::Application::IWindow& m_window;
		PixelPad::Infrastructure::EventBus::SubscriptionToken m_windowCloseEventToken;
		PixelPad::Infrastructure::EventBus::SubscriptionToken m_windowResizeEventToken;
	};
}