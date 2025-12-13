#pragma once

#include "Graphics/IUIComponent.hpp"
#include "Geometries/Transform.hpp"
#include "Graphics/ISprite.hpp"

#include <memory>

namespace PixelPad::Application
{
	class IRenderer;
}

namespace PixelPad::Infrastructure
{
	class UIComponent : public PixelPad::Application::IUIComponent
	{
	public:
		UIComponent(PixelPad::Core::Transform transform, std::unique_ptr<PixelPad::Application::ISprite> sprite);
		void Render(PixelPad::Application::IRenderer& renderer) override;
		void SetSprite(std::unique_ptr<PixelPad::Application::ISprite> sprite) override;
		const PixelPad::Core::Transform& GetTransform() const override { return m_transform; }

	private:
		PixelPad::Core::Transform m_transform;
		std::unique_ptr<PixelPad::Application::ISprite> m_sprite;
	};
}