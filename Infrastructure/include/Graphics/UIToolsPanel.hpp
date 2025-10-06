#pragma once

#include "Graphics/IUIPanel.hpp"
#include "Graphics/UIButton.hpp"
#include "Graphics/Factories/ISpriteFactory.hpp"
#include "Buses/EventBus.hpp"

#include <array>
#include <memory>

namespace PixelPad::Application
{
	class IRenderer;
}

namespace PixelPad::Infrastructure
{
	class UIToolsPanel : public PixelPad::Application::IUIPanel
	{
	public:
		UIToolsPanel(PixelPad::Application::ISpriteFactory& spriteFactory, PixelPad::Infrastructure::EventBus& eventBus);
		void Render(PixelPad::Application::IRenderer& renderer) override;

	private:
		void CreateToolButtons(PixelPad::Infrastructure::EventBus& eventBus);

	private:
		PixelPad::Application::ISpriteFactory& m_spriteFactory;
		std::vector<std::unique_ptr<PixelPad::Infrastructure::UIButton>> m_buttons;
	};
}