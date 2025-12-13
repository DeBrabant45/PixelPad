#pragma once

#include "Graphics/IUIPanel.hpp"
#include "Graphics/UIButton.hpp"
#include "Graphics/Color.hpp"
#include "Graphics/IUIComponent.hpp"
#include "Graphics/Factories/ISpriteFactory.hpp"
#include "Buses/EventBus.hpp"

#include <array>
#include <memory>

namespace PixelPad::Infrastructure
{
	class UIColorPickerPanel : public PixelPad::Application::IUIPanel
	{
	public:
		UIColorPickerPanel(PixelPad::Application::ISpriteFactory& spriteFactory, PixelPad::Infrastructure::EventBus& eventBus);
		~UIColorPickerPanel();
		void Render(PixelPad::Application::IRenderer& renderer) override;

	private:
		void RegisterEventHandlers();
		void UnregisterEventHandlers();
		void CreateColorPreviewComponent();
		void UpdateColorPreviewComponent(PixelPad::Core::Color color);
		void CreateUIButtons(PixelPad::Infrastructure::EventBus& eventBus);
		std::vector<PixelPad::Core::Color> GetColors();

	private:
		PixelPad::Application::ISpriteFactory& m_spriteFactory;
		PixelPad::Infrastructure::EventBus& m_eventBus;
		std::vector<std::unique_ptr<PixelPad::Infrastructure::UIButton<PixelPad::Core::Color>>> m_buttons;
		std::unique_ptr<PixelPad::Application::IUIComponent> m_colorPreviewComponent;
		PixelPad::Infrastructure::EventBus::SubscriptionToken m_colorChangeToken;
	};
}