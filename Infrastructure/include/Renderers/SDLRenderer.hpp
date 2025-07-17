#pragma once

#include "Renderers/IRenderer.hpp"
#include "Windows/IWindow.hpp"

#include <cstdint>
#include <vector>

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Texture;

namespace PixelPad::Core
{
	class Canvas;
}

namespace PixelPad::Infrastructure
{
	class SDLRenderer : public PixelPad::Application::IRenderer
	{
	public:
		SDLRenderer(PixelPad::Application::IWindow& window);
		~SDLRenderer() override;
		void CreateRenderer();
		void Shutdown() override;
		void ClearScreen() override;
		void Render(const PixelPad::Core::Canvas& canvas) override;
		void Present() override;

	private:
		void CreateCanvasTexture(int width, int height);
		bool UpdateTextures(const std::vector<int>& pixels, int width, int height);

	private:
		PixelPad::Application::IWindow& m_window;
		SDL_Renderer* m_sdlRenderer{ nullptr };
		SDL_Texture* m_canvasTexture{ nullptr };
		int m_canvasWidth{ 0 };
		int m_canvasHeight{ 0 };
	};
}