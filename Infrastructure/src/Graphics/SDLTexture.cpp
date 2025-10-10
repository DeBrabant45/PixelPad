#include "Graphics/SDLTexture.hpp"

namespace PixelPad::Infrastructure
{
	SDLTexture::SDLTexture(SDL_Texture* texture, int width, int height) : 
		m_texture(texture), 
		m_width(width), 
		m_height(height)
	{

	}

	SDLTexture::~SDLTexture()
	{
		if (m_texture)
		{
			SDL_DestroyTexture(m_texture);
			m_texture = nullptr;
		}
	}

	int SDLTexture::GetWidth() const
	{
		return m_width;
	}

	int SDLTexture::GetHeight() const
	{
		return m_height;
	}

	SDL_Texture* SDLTexture::GetSDLTexture() const
	{
		return m_texture;
	}
} 