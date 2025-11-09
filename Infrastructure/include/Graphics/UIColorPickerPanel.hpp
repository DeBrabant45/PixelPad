#pragma once

#include "Graphics/IUIPanel.hpp"
#include "Graphics/UIButton.hpp"
#include "Graphics/Color.hpp"
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
		void Render(PixelPad::Application::IRenderer& renderer) override;

	private:
		void CreateButtons(PixelPad::Infrastructure::EventBus& eventBus);

	private:
		PixelPad::Application::ISpriteFactory& m_spriteFactory;
		std::vector<std::unique_ptr<PixelPad::Infrastructure::UIButton<PixelPad::Core::Color>>> m_buttons;
	};
}