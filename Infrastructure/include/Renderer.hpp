#pragma once

class SDL_Renderer;

namespace PixelPad::Infrastructure
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

	private:
		SDL_Renderer* m_renderer{};
	};
}