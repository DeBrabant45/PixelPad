#pragma once

#include "Renderer.hpp"
#include "Graphics/Canvas.hpp"
#include "Window.hpp"
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
		PixelPad::Infrastructure::Window m_window;
		PixelPad::Infrastructure::Renderer m_renderer;
		PixelPad::Core::Canvas m_canvas;
		PixelPad::Application::DrawService m_drawService;
		PixelPad::Presentation::CanvasController m_canvasController;
	};
}