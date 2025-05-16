#pragma once

#include "Renderers/SDLRenderer.hpp"
#include "Graphics/Canvas.hpp"
#include "Windows/SDLWindow.hpp"
#include "Services/DrawService.hpp"
#include "Controllers/CanvasController.hpp"

namespace PixelPad::Presentation
{
	class PixelPadApplication
	{
	public:
		PixelPadApplication();
		~PixelPadApplication();
		void Run();

	private:
		void Shutdown();

	private:
		PixelPad::Infrastructure::SDLWindow m_window;
		PixelPad::Infrastructure::SDLRenderer m_renderer;
		PixelPad::Core::Canvas m_canvas;
		PixelPad::Application::DrawService m_drawService;
		PixelPad::Presentation::CanvasController m_canvasController;
	};
}