#include "PixelPadApplication.hpp"
#include "Events/WindowCloseEvent.hpp"

namespace PixelPad::Presentation
{
    PixelPadApplication::PixelPadApplication() :
        m_eventBus(),
        m_assetPathProvider(),
        m_window(800, 600, "PixelPad", false, m_assetPathProvider),
        m_renderer(m_window),
        m_input(m_eventBus),
        m_textureManager(m_renderer, m_assetPathProvider),
        m_spriteFactory(m_textureManager),
        m_uiRoot(m_spriteFactory, m_eventBus),
        m_canvas(720, 499, 0xFFFFFFFF),
        m_toolbox(m_canvas),
        m_drawService(m_canvas, m_toolbox),
        m_canvasViewport(m_canvas.GetWidth(), m_canvas.GetHeight(), 70, 30),
        m_canvasController(m_canvas, m_drawService, m_eventBus, m_canvasViewport),
        m_windowController(m_window, m_eventBus),
        m_rendererController(m_renderer, m_canvas, m_uiRoot, m_canvasViewport),
        m_uiController(m_uiRoot, m_eventBus)
    {

    }

    PixelPadApplication::~PixelPadApplication()
    {
        Shutdown();
    }

    void PixelPadApplication::Run()
    {
        while (m_windowController.IsOpen())
        {
            m_input.PollEvents();
			m_rendererController.Render();
        }
    }

    void PixelPadApplication::Shutdown()
    {
        m_renderer.Shutdown();
        m_window.Shutdown();
    }
}