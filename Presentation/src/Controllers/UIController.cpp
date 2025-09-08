#include "Controllers/UIController.hpp"
#include "Graphics/UIRoot.hpp"
#include "Graphics/IUIButton.hpp"
#include "Events/ToolTypeChangedEvent.hpp"
#include "Events/UIButtonClickedEvent.hpp"

namespace PixelPad::Presentation
{
	UIController::UIController(
		PixelPad::Application::IUIRoot& uiRoot, 
		PixelPad::Infrastructure::EventBus& eventBus) :
		m_uiRoot(uiRoot),
		m_eventBus(eventBus),
		m_buttonClickedEventToken()
	{
		RegisterEventHandlers();
	}

	void UIController::RegisterEventHandlers()
	{
		m_buttonClickedEventToken = m_eventBus.Subscribe<PixelPad::Application::UIButtonClickedEvent>(
			[this](const PixelPad::Application::UIButtonClickedEvent& evt)
			{
				if (evt.ClickResult.ButtonId == "PencilTool")
					m_eventBus.Publish(PixelPad::Application::ToolTypeChangedEvent{ PixelPad::Application::ToolType::Pencil });
			});
	}

	UIController::~UIController()
	{
		UnregisterEventHandlers();
	}

	void UIController::UnregisterEventHandlers()
	{

	}
}