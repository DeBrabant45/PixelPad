#pragma once

class SDL_Renderer;

namespace Infrastructure
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