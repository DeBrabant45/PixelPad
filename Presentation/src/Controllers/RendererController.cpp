#include "Controllers/RendererController.hpp"
#include "Renderers/IRenderer.hpp"
#include "Graphics/IUIRoot.hpp"

namespace PixelPad::Presentation
{
	RendererController::RendererController(
		PixelPad::Application::IRenderer& renderer, 
		PixelPad::Core::Canvas& canvas,
		PixelPad::Application::IUIRoot& uiRoot) :
		m_uiRoot(uiRoot),
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
		m_uiRoot.Render(m_renderer);
		m_renderer.Present();
	}
}