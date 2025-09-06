#include "Graphics/UIToolsPanel.hpp"

namespace PixelPad::Infrastructure
{
	UIToolsPanel::UIToolsPanel(PixelPad::Application::ITextureManager& textureManager) :
		m_textureManager(textureManager)
	{
		auto texture = m_textureManager.LoadTexture("C:/Assets/sample.bmp");
		m_button = new PixelPad::Infrastructure::UIButton(400, 400, 50, 50, std::move(texture));
	}

	void UIToolsPanel::Render(PixelPad::Application::IRenderer& renderer)
	{
		m_button->Render(renderer);
	}

	void UIToolsPanel::HandleClick(int x, int y)
	{

	}
}