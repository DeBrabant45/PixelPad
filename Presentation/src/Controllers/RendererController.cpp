#include "Controllers/RendererController.hpp"
#include "Renderers/IRenderer.hpp"

namespace PixelPad::Presentation
{
	RendererController::RendererController(
		PixelPad::Infrastructure::IRenderer& renderer, 
		PixelPad::Core::Canvas& canvas) : 
		m_renderer(renderer),
		m_canvas(canvas)
	{
		RegisterEventHandlers();
	}

	void RendererController::RegisterEventHandlers()
	{

	}

	RendererController::~RendererController()
	{
		UnregisterEventHandlers();
	}

	void RendererController::UnregisterEventHandlers()
	{

	}

	void RendererController::Render()
	{
		m_renderer.ClearScreen();
		m_renderer.Render(m_canvas);
		m_renderer.Present();
	}
}