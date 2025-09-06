#pragma once

#include "Graphics/ITexture.hpp"
#include <SDL3/SDL.h>

namespace PixelPad::Infrastructure
{
	class SDLTexture : public PixelPad::Application::ITexture
	{
	public:
		SDLTexture(SDL_Texture* texture, int width, int height);
		~SDLTexture() override;
		int GetWidth() const override;
		int GetHeight() const override;
		SDL_Texture* GetSDLTexture() const;

	private:
		SDL_Texture* m_texture;
		int m_width;
		int m_height;
	};
}