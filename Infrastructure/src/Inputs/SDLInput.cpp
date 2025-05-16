#include "Inputs/SDLInput.hpp"
#include "Windows/IWindow.hpp"
#include "Events/WindowCloseEvent.hpp"
#include "Events/MouseButtonEvent.hpp"

#include <SDL3/SDL.h>

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
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                m_eventBus.Publish(WindowCloseEvent{ true });
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                m_eventBus.Publish(MouseButtonEvent{ event.button.x, event.button.y, true });
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                m_eventBus.Publish(MouseButtonEvent{ event.button.x, event.button.y, false });
                break;
            }
        }
    }
}