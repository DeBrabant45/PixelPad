#pragma once

#include "Buses/EventBus.hpp"

namespace PixelPad::Infrastructure
{
	class IWindow;
}

namespace PixelPad::Presentation
{
	class WindowController
	{
	public:
		WindowController(PixelPad::Infrastructure::IWindow& window, PixelPad::Infrastructure::EventBus& m_eventBus);
		~WindowController();
		void Resize(int newWidth, int newHeight);
		void Close();
		bool IsOpen() const;

	private:
		void RegisterEventHandlers();
		void UnregisterEventHandlers();

	private:
		PixelPad::Infrastructure::EventBus& m_eventBus;
		PixelPad::Infrastructure::IWindow& m_window;
		PixelPad::Infrastructure::EventBus::SubscriptionToken m_windowCloseEventToken;
	};
}