#include "Graphics/ButtonSprite.hpp"

namespace PixelPad::Application
{
	ButtonSprite::ButtonSprite(const PixelPad::Core::Transform& transform, const ButtonSpriteTexture buttonSpriteTexture) :
		Sprite(transform, buttonSpriteTexture.UnClicked),
		m_textures(buttonSpriteTexture),
		m_currentState(ButtonState::UnClicked)
	{

	}

	void ButtonSprite::SetState(ButtonState state)
	{
		m_currentState = state;
		switch (state)
		{
		case PixelPad::Application::ButtonState::UnClicked:
			Texture = m_textures.UnClicked;
			break;
		case PixelPad::Application::ButtonState::Clicked:
			Texture = m_textures.Clicked;
			break;
		case PixelPad::Application::ButtonState::Hover:
			Texture = m_textures.Hover;
			break;
		default:
			break;
		}
	}
}