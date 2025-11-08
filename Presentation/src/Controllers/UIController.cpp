#include "Controllers/UIController.hpp"
#include "Graphics/UIRoot.hpp"
#include "Graphics/IUIButton.hpp"
#include "Graphics/Color.hpp"
#include "Events/ToolTypeChangedEvent.hpp"
#include "Events/ColorChangedEvent.hpp"
#include "Events/UIButtonClickedEvent.hpp"

#include <map>

namespace PixelPad::Presentation
{
	UIController::UIController(
		PixelPad::Application::IUIRoot& uiRoot, 
		PixelPad::Infrastructure::EventBus& eventBus) :
		m_uiRoot(uiRoot),
		m_eventBus(eventBus),
		m_buttonClickedColorEventToken(),
		m_buttonClickedToolTypeEventToken()
	{
		RegisterEventHandlers();
	}

	void UIController::RegisterEventHandlers()
	{
		m_buttonClickedColorEventToken = m_eventBus.Subscribe<PixelPad::Application::UIButtonClickedEvent<PixelPad::Core::Color>>(
			[this](const PixelPad::Application::UIButtonClickedEvent<PixelPad::Core::Color>& evt)
			{
				m_eventBus.Publish(PixelPad::Application::ColorChangedEvent(evt.Value));
			});

		m_buttonClickedToolTypeEventToken = m_eventBus.Subscribe<PixelPad::Application::UIButtonClickedEvent<PixelPad::Core::ToolType>>(
			[this](const PixelPad::Application::UIButtonClickedEvent<PixelPad::Core::ToolType>& evt)
			{
				m_eventBus.Publish(PixelPad::Application::ToolTypeChangedEvent(evt.Value));
			});
	}

	UIController::~UIController()
	{
		UnregisterEventHandlers();
	}

	void UIController::UnregisterEventHandlers()
	{
		m_eventBus.Unsubscribe<PixelPad::Application::UIButtonClickedEvent<PixelPad::Core::Color>>(m_buttonClickedColorEventToken);
		m_eventBus.Unsubscribe<PixelPad::Application::UIButtonClickedEvent<PixelPad::Core::ToolType>>(m_buttonClickedToolTypeEventToken);
	}
}