#include "Graphics/UIRoot.hpp"
#include "Graphics/UIToolsPanel.hpp"
#include "Graphics/ITextureManager.hpp"
#include "Graphics/ITexture.hpp"
#include "Graphics/ISprite.hpp"
#include "Graphics/SDLTexture.hpp"
#include "Renderers/IRenderer.hpp"
#include "Graphics/Factories/ISpritefactory.hpp"
#include "Geometries/Transform.hpp"
#include "Graphics/UIColorPickerPanel.hpp"

namespace PixelPad::Infrastructure
{
	UIRoot::UIRoot(PixelPad::Application::ISpriteFactory& spriteFactory, PixelPad::Infrastructure::EventBus& eventBus) :
		m_backgroundSprite(nullptr)
	{
		auto transform = PixelPad::Core::Transform(0, 0, 0, 800, 600);
		m_backgroundSprite = spriteFactory.CreateSprite("retro-frame.bmp", transform);
		m_panels[0] = std::make_unique<UIToolsPanel>(spriteFactory, eventBus);
		m_panels[1] = std::make_unique<UIColorPickerPanel>(spriteFactory, eventBus);
	}

	void UIRoot::Render(PixelPad::Application::IRenderer& renderer)
	{
		renderer.Render(m_backgroundSprite.get());
		for (size_t i = 0; i < m_panels.size(); i++)
		{
			if (m_panels[i])
			{
				m_panels[i]->Render(renderer);
			}
		}
	}
}