#pragma once

#include "Renderers/IRenderer.hpp"
#include "Windows/IWindow.hpp"

#include <cstdint>
#include <vector>
#include <string>

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Texture;

namespace PixelPad::Core
{
	class Canvas;
}

namespace PixelPad::Application
{
	class CanvasViewport;
	class ISprite;
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
		void Render(const PixelPad::Core::Canvas& canvas, PixelPad::Application::CanvasViewport& canvasViewport) override;
		void Render(PixelPad::Application::ISprite* sprite) override;
		void Present() override;
		SDL_Texture* CreateSDLTexture(const std::string& filePath);

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