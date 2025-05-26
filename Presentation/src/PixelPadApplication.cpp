#include "PixelPadApplication.hpp"
#include "Events/WindowCloseEvent.hpp"

namespace PixelPad::Presentation
{
    PixelPadApplication::PixelPadApplication() :
		m_eventBus(),
        m_window(640, 480, "PixelPad"),
        m_renderer(m_window),
		m_input(m_eventBus),
        m_canvas(m_window.GetWidth(), m_window.GetHeight()),
        m_drawService(m_canvas),
        m_canvasController(m_canvas, m_drawService, m_eventBus),
		m_windowController(m_window, m_eventBus)
    {

    }

    PixelPadApplication::~PixelPadApplication()
    {
        Shutdown();
    }

    void PixelPadApplication::Run()
    {
        bool hasResized = false;
        bool canvasFilled = false;

        while (m_windowController.IsOpen())
        {
            m_input.PollEvents();

            m_renderer.ClearScreen();

            // Sample fill operations
            if (!canvasFilled)
            {
                m_canvasController.Fill();
                canvasFilled = true;
            }

			// Sample drawing operations
            m_canvasController.DrawPixel(100, 100, 0xFFFF00FF);
            m_canvasController.DrawLine(50, 50, 200, 200, 0xFF000000);

            m_renderer.Render(m_canvas);
            m_renderer.Present();

            // Sample resize operations
            if (!hasResized)
            {
                m_canvasController.Resize(800, 600);
                m_windowController.Resize(800, 600);
                hasResized = true;
                canvasFilled = false;
            }
        }
    }

    void PixelPadApplication::Shutdown()
    {
        m_renderer.Shutdown();
        m_window.Shutdown();
    }
}