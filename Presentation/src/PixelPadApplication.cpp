#include "PixelPadApplication.hpp"

namespace PixelPad::Presentation
{
    PixelPadApplication::PixelPadApplication() :
		m_eventBus(),
        m_window(640, 480, "PixelPad Application", m_eventBus),
        m_renderer(m_window),
		m_input(m_eventBus),
        m_canvas(m_window.GetWidth(), m_window.GetHeight()),
        m_drawService(m_canvas),
        m_canvasController(m_canvas, m_drawService)
    {

    }

    PixelPadApplication::~PixelPadApplication()
    {
        Shutdown();
    }

    void PixelPadApplication::Run()
    {
        while (m_window.IsOpen())
        {
			m_input.PollEvents();

            m_renderer.ClearScreen();

            m_canvasController.Fill();
            m_canvasController.DrawPixel(100, 100, 0xFFFF00FF);
            m_canvasController.DrawLine(50, 50, 200, 200, 0xFF000000);

            m_renderer.Render(m_canvas);
            m_renderer.Present();
        }
    }

    void PixelPadApplication::Shutdown()
    {
        m_renderer.Shutdown();
        m_window.Shutdown();
    }
}