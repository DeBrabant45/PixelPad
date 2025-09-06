#pragma once

#include "Graphics/IUIButton.hpp"
#include "Graphics/ITexture.hpp"

#include <memory>

namespace PixelPad::Application
{
	class IRenderer;
}

namespace PixelPad::Infrastructure
{
	class UIButton : public PixelPad::Application::IUIButton
	{
	public:
		UIButton(int x, int y, int w, int h, std::shared_ptr<PixelPad::Application::ITexture> texture);
		void Render(PixelPad::Application::IRenderer& renderer) override;
		void OnClick(const std::function<void()>& callback) override;
		void HandleClick(int clickX, int clickY) override;
		PixelPad::Application::Transform GetTransform() const override;

	private:
		PixelPad::Application::Transform m_transform;
		std::shared_ptr<PixelPad::Application::ITexture> m_texture;
		std::function<void()> m_callback;
	};
}