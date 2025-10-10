#pragma once

#include "Graphics/IUIRoot.hpp"
#include "Graphics/IUIPanel.hpp"
#include "Buses/EventBus.hpp"
#include "Graphics/ISprite.hpp"

#include <array>
#include <memory>

namespace PixelPad::Application
{
	class IRenderer;
	class ISpriteFactory;
}

namespace PixelPad::Infrastructure
{
	class UIRoot : public PixelPad::Application::IUIRoot
	{
	public:
		UIRoot(PixelPad::Application::ISpriteFactory& spriteFactory, PixelPad::Infrastructure::EventBus& eventBus);
		void Render(PixelPad::Application::IRenderer& renderer) override;

	private:
		std::array<std::unique_ptr<PixelPad::Application::IUIPanel>, 3> m_panels;
		std::unique_ptr<PixelPad::Application::ISprite> m_backgroundSprite;
	};
}