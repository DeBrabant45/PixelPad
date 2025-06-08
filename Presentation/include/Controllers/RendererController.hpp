#pragma once
#include "Graphics/Canvas.hpp"

namespace PixelPad::Infrastructure
{
	class IRenderer;
}	

namespace PixelPad::Presentation
{
	class RendererController
	{
	public:
		RendererController(PixelPad::Infrastructure::IRenderer& renderer, PixelPad::Core::Canvas& canvas);
		~RendererController();
		void Render();

	private:
		void RegisterEventHandlers();
		void UnregisterEventHandlers();

	private:
		PixelPad::Infrastructure::IRenderer& m_renderer;
		PixelPad::Core::Canvas& m_canvas;
	};
}