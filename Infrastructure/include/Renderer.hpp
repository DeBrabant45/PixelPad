#pragma once

#include "IRenderer.hpp"
#include "IWindow.hpp"

struct SDL_Renderer;
struct SDL_Window;

namespace PixelPad::Core
{
	class Canvas;
}

namespace PixelPad::Infrastructure
{
	class Renderer : public IRenderer
	{
	public:
		Renderer(IWindow& window);
		~Renderer() override;
		void ClearScreen() override;
		void Render(const PixelPad::Core::Canvas& canvas) override;
		void Present() override;
		void Resize(int newWidth, int newHeight) override;
		void Shutdown() override;

	private:
		IWindow& m_window;
		SDL_Renderer* m_sdlRenderer = nullptr;
	};
}