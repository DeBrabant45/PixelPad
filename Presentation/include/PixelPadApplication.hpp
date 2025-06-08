#pragma once

#include "Buses/EventBus.hpp"
#include "Windows/SDLWindow.hpp"
#include "Renderers/SDLRenderer.hpp"
#include "Inputs/SDLInput.hpp"
#include "Graphics/Canvas.hpp"
#include "Services/DrawService.hpp"
#include "Controllers/CanvasController.hpp"
#include "Controllers/WindowController.hpp"
#include "Controllers/RendererController.hpp"

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
		PixelPad::Infrastructure::EventBus m_eventBus;
		PixelPad::Infrastructure::SDLWindow m_window;
		PixelPad::Infrastructure::SDLRenderer m_renderer;
		PixelPad::Infrastructure::SDLInput m_input;
		PixelPad::Core::Canvas m_canvas;
		PixelPad::Application::DrawService m_drawService;
		PixelPad::Presentation::CanvasController m_canvasController;
		PixelPad::Presentation::WindowController m_windowController;
		PixelPad::Presentation::RendererController m_rendererController;
	};
}