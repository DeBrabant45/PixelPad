#pragma once
#include "Graphics/Canvas.hpp"

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
		RendererController(PixelPad::Application::IRenderer& renderer, PixelPad::Core::Canvas& canvas, PixelPad::Application::IUIRoot& uiRoot);
		~RendererController();
		void Render();

	private:
		void RegisterEventHandlers();
		void UnregisterEventHandlers();

	private:
		PixelPad::Application::IUIRoot& m_uiRoot;
		PixelPad::Application::IRenderer& m_renderer;
		PixelPad::Core::Canvas& m_canvas;
	};
}