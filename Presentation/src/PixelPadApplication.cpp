#include "PixelPadApplication.hpp"

namespace PixelPad::Presentation
{
    PixelPadApplication::PixelPadApplication() :
        m_window(640, 480, "PixelPad Application"),
        m_renderer(m_window),
        m_canvas(m_window.GetWidth(), m_window.GetHeight()),
        m_drawService(m_canvas)
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
            m_window.PollEvents();

            // Optional but harmless
            m_renderer.ClearScreen();

            // Fill canvas with white (opaque!)
            m_canvas.Fill(0xFFFFFFFF);

            // Draw something visible
            m_drawService.DrawPixel(100, 100, 0xFFFF00FF);     // Magenta
            m_drawService.DrawLine(50, 50, 200, 200, 0xFF000000); // Green

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