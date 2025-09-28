#pragma once
#include "Graphics/Canvas.hpp"
#include "Graphics/CanvasViewport.hpp"

namespace PixelPad::Application
{
	class IRenderer;
	class IUIRoot;
}	

namespace PixelPad::Presentation
{
	class RendererController
	{
	public:
		RendererController(
			PixelPad::Application::IRenderer& renderer, 
			PixelPad::Core::Canvas& canvas, 
			PixelPad::Application::IUIRoot& uiRoot,
			PixelPad::Application::CanvasViewport& canvasViewport);
		~RendererController();
		void Render();

	private:
		void RegisterEventHandlers();
		void UnregisterEventHandlers();

	private:
		PixelPad::Application::IUIRoot& m_uiRoot;
		PixelPad::Application::IRenderer& m_renderer;
		PixelPad::Core::Canvas& m_canvas;
		PixelPad::Application::CanvasViewport& m_canvasViewport;
	};
}