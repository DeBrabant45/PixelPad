#pragma once

#include "Graphics/IUIPanel.hpp"
#include "Graphics/UIButton.hpp"
#include "Graphics/ITextureManager.hpp"
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
		UIToolsPanel(PixelPad::Application::ITextureManager& textureManager, PixelPad::Infrastructure::EventBus& eventBus);
		void Render(PixelPad::Application::IRenderer& renderer) override;

	private:
		void CreateToolButtons(PixelPad::Infrastructure::EventBus& eventBus);

	private:
		PixelPad::Application::ITextureManager& m_textureManager;
		std::vector<std::unique_ptr<PixelPad::Infrastructure::UIButton>> m_buttons;
	};
}