#pragma once

#include "Graphics/IUIPanel.hpp"
#include "Graphics/UIButton.hpp"
#include "Graphics/ITextureManager.hpp"

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
		UIToolsPanel(PixelPad::Application::ITextureManager& textureManager);
		void Render(PixelPad::Application::IRenderer& renderer) override;
		void HandleClick(int x, int y) override;

	private:
		PixelPad::Infrastructure::UIButton* m_button;
		PixelPad::Application::ITextureManager& m_textureManager;
	};
}