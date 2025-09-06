#pragma once

#include "Graphics/IUIRoot.hpp"
#include "Graphics/IUIPanel.hpp"

#include <array>
#include <memory>

namespace PixelPad::Application
{
	class IRenderer;
	class ITextureManager;
}

namespace PixelPad::Infrastructure
{
	class UIRoot : public PixelPad::Application::IUIRoot
	{
	public:
		UIRoot(PixelPad::Application::ITextureManager& textureManager);
		void Render(PixelPad::Application::IRenderer& renderer) override;
		void HandleClick(int x, int y) override;

	private:
		std::array<std::unique_ptr<PixelPad::Application::IUIPanel>, 3> m_panels;
	};
}