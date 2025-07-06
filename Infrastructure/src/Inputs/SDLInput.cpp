#include "Inputs/SDLInput.hpp"
#include "Windows/IWindow.hpp"
#include "Events/WindowCloseEvent.hpp"
#include "Events/MouseButtonEvent.hpp"
#include "Events/WindowResizeEvent.hpp"
#include "Events/ToolTypeChangedEvent.hpp"
#include "Enums/MouseButton.hpp"

#include <SDL3/SDL.h>
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
            ProcessMouseMotionEvent(event.type, event.motion);
            ProcessWindowResizeEvent(event.type, event.window);
            ProcessKeyboardEvent(event.type, event.key);
        }
    }

    void SDLInput::ProcessWindowCloseEvent(unsigned int type)
    {
        if (type != SDL_EVENT_QUIT && type != SDL_EVENT_WINDOW_CLOSE_REQUESTED)
            return;

        m_eventBus.Publish(PixelPad::Application::WindowCloseEvent{ true });
    }

    void SDLInput::ProcessWindowResizeEvent(unsigned int type, const SDL_WindowEvent& window)
    {
        if (type != SDL_EVENT_WINDOW_RESIZED)
            return;

        int width = window.data1;
        int height = window.data2;
        m_eventBus.Publish(PixelPad::Application::WindowResizeEvent{ width, height });
        std::cerr << "Window Resize command init: " << width << "x" << height << std::endl;
    }

    void SDLInput::ProcessMouseButtonEvent(unsigned int type, const SDL_MouseButtonEvent& button)
    {
        if (type != SDL_EVENT_MOUSE_BUTTON_DOWN && type != SDL_EVENT_MOUSE_BUTTON_UP)
            return;

        bool isPressed = type == SDL_EVENT_MOUSE_BUTTON_DOWN;
        int x = button.x;
        int y = button.y;

        switch (button.button)
        {
        case SDL_BUTTON_LEFT:
            m_eventBus.Publish(PixelPad::Application::MouseButtonEvent( x, y, isPressed, PixelPad::Application::MouseButton::Left));
            break;
        case SDL_BUTTON_RIGHT:
            m_eventBus.Publish(PixelPad::Application::MouseButtonEvent( x, y, isPressed, PixelPad::Application::MouseButton::Right));
            break;
        case SDL_BUTTON_MIDDLE:
            m_eventBus.Publish(PixelPad::Application::MouseButtonEvent( x, y, isPressed, PixelPad::Application::MouseButton::Middle));
            break;
        default:
            break;
        }
    }

    void SDLInput::ProcessMouseMotionEvent(unsigned int type, const SDL_MouseMotionEvent& motion)
    {
        if (type != SDL_EVENT_MOUSE_MOTION)
            return;

        float x = 0.f, y = 0.f;
        Uint32 buttons = SDL_GetMouseState(&x, &y);

        if (buttons & SDL_BUTTON_LMASK)
        {
            m_eventBus.Publish(PixelPad::Application::MouseButtonEvent(static_cast<int>(x), static_cast<int>(y), true, PixelPad::Application::MouseButton::Left));
        }
        if (buttons & SDL_BUTTON_RMASK)
        {
            m_eventBus.Publish(PixelPad::Application::MouseButtonEvent( static_cast<int>(x), static_cast<int>(y), true, PixelPad::Application::MouseButton::Right));
        }
        if (buttons & SDL_BUTTON_MMASK)
        {
            m_eventBus.Publish(PixelPad::Application::MouseButtonEvent(static_cast<int>(x), static_cast<int>(y), true, PixelPad::Application::MouseButton::Middle));
        }
    }

    void SDLInput::ProcessKeyboardEvent(unsigned int type, const SDL_KeyboardEvent& keyEvent)
    {
        if (type != SDL_EVENT_KEY_DOWN)
            return;

        switch (keyEvent.key)   
        {
        case SDLK_1:
            m_eventBus.Publish(PixelPad::Application::ToolTypeChangedEvent{ PixelPad::Application::ToolType::Pencil });
			break;

        case SDLK_2:
            m_eventBus.Publish(PixelPad::Application::ToolTypeChangedEvent{ PixelPad::Application::ToolType::Line });
			break;

        case SDLK_3:
            m_eventBus.Publish(PixelPad::Application::ToolTypeChangedEvent{ PixelPad::Application::ToolType::Eraser });
            break;

        case SDLK_4:
            m_eventBus.Publish(PixelPad::Application::ToolTypeChangedEvent{ PixelPad::Application::ToolType::Fill });
            break;

        default:
            break;
        }
    }
}