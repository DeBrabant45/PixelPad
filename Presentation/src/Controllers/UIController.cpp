#include "Controllers/UIController.hpp"
#include "Graphics/UIRoot.hpp"

namespace PixelPad::Presentation
{
	UIController::UIController(
		PixelPad::Application::IUIRoot& uiRoot, 
		PixelPad::Infrastructure::EventBus& eventBus) :
		m_uiRoot(uiRoot),
		m_eventBus(eventBus)
	{
		RegisterEventHandlers();
	}

	void UIController::RegisterEventHandlers()
	{

	}

	UIController::~UIController()
	{
		UnregisterEventHandlers();
	}

	void UIController::UnregisterEventHandlers()
	{

	}
}