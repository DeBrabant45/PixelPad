#include "Controllers/UIController.hpp"
#include "Graphics/UIRoot.hpp"
#include "Graphics/IUIButton.hpp"
#include "Events/ToolTypeChangedEvent.hpp"
#include "Events/UIButtonClickedEvent.hpp"

#include <map>

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
		static const std::unordered_map<std::string, PixelPad::Application::ToolType> buttonToToolMap =
		{
			{"PencilTool", PixelPad::Application::ToolType::Pencil},
			{"EraserTool", PixelPad::Application::ToolType::Eraser},
			{"FillTool", PixelPad::Application::ToolType::Fill},
			{"LineTool", PixelPad::Application::ToolType::Line},
			{"RectangleTool", PixelPad::Application::ToolType::Rectangle},
			{"EllipseTool", PixelPad::Application::ToolType::Ellipse}
		};

		m_buttonClickedEventToken = m_eventBus.Subscribe<PixelPad::Application::UIButtonClickedEvent>(
			[this](const PixelPad::Application::UIButtonClickedEvent& evt)
			{
				auto it = buttonToToolMap.find(evt.ClickResult.ButtonId);
				if (it != buttonToToolMap.end())
				{
					m_eventBus.Publish(PixelPad::Application::ToolTypeChangedEvent{ it->second });
				}
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