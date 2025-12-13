#include "Graphics/UIComponent.hpp"
#include "Graphics/IRenderable.hpp"
#include "Renderers/IRenderer.hpp"

namespace PixelPad::Infrastructure
{
	UIComponent::UIComponent(PixelPad::Core::Transform transform, std::unique_ptr<PixelPad::Application::ISprite> sprite) :
		m_transform(std::move(transform)),
		m_sprite(std::move(sprite))
	{

	}

	void UIComponent::Render(PixelPad::Application::IRenderer& renderer)
	{
		if (!m_sprite->GetTexture().get())
			return;

		renderer.Render(m_sprite.get());
	}

	void UIComponent::SetSprite(std::unique_ptr<PixelPad::Application::ISprite> sprite)
	{
		if (!sprite->GetTexture().get())
			return;

		m_sprite = std::move(sprite);
	}
}