#include "PixelPadApplication.hpp"
#include "Events/WindowCloseEvent.hpp"

namespace PixelPad::Presentation
{
    PixelPadApplication::PixelPadApplication() :
		m_eventBus(),
        m_window(640, 480, "PixelPad"),
        m_renderer(m_window),
		m_input(m_eventBus),
        m_canvas(800, 600, 0xFFFFFFFF),
        m_drawService(m_canvas),
        m_canvasController(m_canvas, m_drawService, m_eventBus),
		m_windowController(m_window, m_eventBus),
		m_rendererController(m_renderer, m_canvas)
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