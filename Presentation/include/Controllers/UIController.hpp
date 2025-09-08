#pragma once

#include "Buses/EventBus.hpp"

namespace PixelPad::Application
{
	class IUIRoot;
}

namespace PixelPad::Presentation
{
	class UIController
	{
	public:
		UIController(PixelPad::Application::IUIRoot& uiRoot, PixelPad::Infrastructure::EventBus& eventBus);
		~UIController();

	private:
		void RegisterEventHandlers();
		void UnregisterEventHandlers();

	private:
		PixelPad::Application::IUIRoot& m_uiRoot;
		PixelPad::Infrastructure::EventBus& m_eventBus;
		PixelPad::Infrastructure::EventBus::SubscriptionToken m_buttonClickedEventToken;
	};
}