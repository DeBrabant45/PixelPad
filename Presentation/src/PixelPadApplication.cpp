#include "PixelPadApplication.hpp"
#include "Events/WindowCloseEvent.hpp"

#include <iostream>

namespace PixelPad::Presentation
{
    PixelPadApplication::PixelPadApplication() :
        m_eventBus(),
        m_window(800, 600, "PixelPad", false),
        m_renderer(m_window),
        m_input(m_eventBus),
        m_textureManager(m_renderer),
        m_uiRoot(m_textureManager, m_eventBus),
        m_canvas(720, 525, 0xFFFFFFFF),
        m_toolbox(m_canvas),
        m_drawService(m_canvas, m_toolbox),
        m_canvasController(m_canvas, m_drawService, m_eventBus),
        m_windowController(m_window, m_eventBus),
        m_rendererController(m_renderer, m_canvas, m_uiRoot),
        m_uiController(m_uiRoot, m_eventBus)
    {
        std::cout << "Size of PixelPadApplication: " << sizeof(*this) << " bytes" << std::endl; // 392
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