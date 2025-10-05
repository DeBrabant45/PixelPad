#pragma once

#include "Graphics/Sprite.hpp"
#include "ITexture.hpp"
#include <vector>

namespace PixelPad::Application
{
	enum class ButtonState
	{
		UnClicked = 0,
		Clicked = 1,
		Hover = 2
	};

	struct ButtonSpriteTexture
	{
		std::shared_ptr<ITexture> UnClicked;
		std::shared_ptr<ITexture> Clicked;
		std::shared_ptr<ITexture> Hover;
	};

	class ButtonSprite : public Sprite
	{
	public:
		ButtonSprite(const PixelPad::Core::Transform& transform, const ButtonSpriteTexture buttonSpriteTexture);
		void SetState(ButtonState state);

	private:
		ButtonSpriteTexture m_textures;
		ButtonState m_currentState;
	};
}