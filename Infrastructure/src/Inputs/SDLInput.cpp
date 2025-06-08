#include "Inputs/SDLInput.hpp"
#include "Windows/IWindow.hpp"
#include "Events/WindowCloseEvent.hpp"
#include "Events/MouseButtonEvent.hpp"

#include <SDL3/SDL.h>
#include <Events/WindowResizeEvent.hpp>
#include <iostream>

namespace PixelPad::Infrastructure
{
	SDLInput::SDLInput(EventBus& eventBus) :
        m_eventBus(eventBus)
    {

    }

    void SDLInput::PollEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ProcessWindowCloseEvent(event.type);
            ProcessMouseButtonEvent(event.type, event.button);
            if (event.type == SDL_EVENT_WINDOW_RESIZED)
            {
                int width = event.window.data1;
                int height = event.window.data2;
                m_eventBus.Publish(WindowResizeEvent{ width, height });
                std::cerr << "Window Resize command init: " << width << "x" << height << std::endl;
            }
        }
    }

    void SDLInput::ProcessWindowCloseEvent(unsigned int type)
    {
        if (type != SDL_EVENT_QUIT && type != SDL_EVENT_WINDOW_CLOSE_REQUESTED)
            return;

        m_eventBus.Publish(WindowCloseEvent{ true });
    }

    void SDLInput::ProcessMouseButtonEvent(unsigned int type, SDL_MouseButtonEvent& button)
    {
        if (type != SDL_EVENT_MOUSE_BUTTON_DOWN && type != SDL_EVENT_MOUSE_BUTTON_UP)
            return;

        bool isPressed = type == SDL_EVENT_MOUSE_BUTTON_DOWN;
        int x = button.x;
        int y = button.y;

        switch (button.button)
        {
        case SDL_BUTTON_LEFT:
            m_eventBus.Publish(MouseButtonEvent{ x, y, isPressed, MouseButton::Left });
            break;
        case SDL_BUTTON_RIGHT:
            m_eventBus.Publish(MouseButtonEvent{ x, y, isPressed, MouseButton::Right });
            break;
        case SDL_BUTTON_MIDDLE:
            m_eventBus.Publish(MouseButtonEvent{ x, y, isPressed, MouseButton::Middle });
            break;
        default:
            break;
        }
    }
}