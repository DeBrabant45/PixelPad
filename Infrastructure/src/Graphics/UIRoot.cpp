#include "Graphics/UIRoot.hpp"
#include "Graphics/UIToolsPanel.hpp"
#include "Graphics/ITextureManager.hpp"

namespace PixelPad::Infrastructure
{
	UIRoot::UIRoot(PixelPad::Application::ITextureManager& textureManager)
	{
		m_panels[0] = std::make_unique<UIToolsPanel>(textureManager);
	}

	void UIRoot::Render(PixelPad::Application::IRenderer& renderer)
	{
		for (size_t i = 0; i < m_panels.size(); i++)
		{
			if (m_panels[i])
			{
				m_panels[i]->Render(renderer);
			}
		}
	}

	void UIRoot::HandleClick(int x, int y)
	{
		for (size_t i = 0; i < m_panels.size(); i++)
		{
			if (m_panels[i])
			{
				m_panels[i]->HandleClick(x, y);
			}
		}
	}
}