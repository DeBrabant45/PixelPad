#pragma once

#include "Graphics/Sprite.hpp"
#include "Graphics/IButtonSprite.hpp"
#include "Graphics/ITexture.hpp"
#include <vector>

namespace PixelPad::Application
{
	struct ButtonSpriteTexture
	{
		std::shared_ptr<ITexture> UnClicked;
		std::shared_ptr<ITexture> Clicked;
	};

	class ButtonSprite : public Sprite, public IButtonSprite
	{
	public:
		ButtonSprite(const PixelPad::Core::Transform& transform, const ButtonSpriteTexture buttonSpriteTexture);
		void SetState(ButtonState state) override;

	private:
		ButtonSpriteTexture m_textures;
		ButtonState m_currentState;
	};
}