#include "Windows/SDLWindow.hpp"
#include "Events/WindowCloseEvent.hpp"

#include <SDL3/SDL.h>
#include <iostream>

namespace PixelPad::Infrastructure
{
	SDLWindow::SDLWindow(
		int width, 
		int height, 
		const char* title, 
		EventBus& eventBus) :
		m_width(width),
		m_height(height),
		m_isOpen(true),
		m_eventBus(eventBus)
	{
		RegisterEventHandlers();
		CreateSDLWindow(width, height, title);
	}

	void SDLWindow::RegisterEventHandlers()
	{
		m_eventBus.Subscribe<WindowCloseEvent>([this](const WindowCloseEvent&) {
			this->Close();
			});
	}

	void SDLWindow::CreateSDLWindow(int width, int height, const char* title)
	{
		if (!SDL_Init(SDL_INIT_VIDEO))
		{
			m_isOpen = false;
			std::cerr << "SDL Init failed: " << SDL_GetError() << std::endl;
			return;
		}
		m_window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL);
		if (!m_window)
		{
			m_isOpen = false;
			std::cerr << "SDL Window Creation failed: " << SDL_GetError() << std::endl;
			return;
		}

		m_isOpen = true;
	}

	SDLWindow::~SDLWindow()
	{
		Shutdown();
	}

	int SDLWindow::GetWidth() const
	{
		return m_width;
	}

	int SDLWindow::GetHeight() const
	{
		return m_height;
	}

	void SDLWindow::Resize(int newWidth, int newHeight)
	{
		if (m_window == nullptr)
		{
			m_isOpen = false;
			return;
		}

		SDL_SetWindowSize(m_window, newWidth, newHeight);
		m_width = newWidth;
		m_height = newHeight;
	}

	bool SDLWindow::IsOpen() const
	{
		return m_isOpen;
	}

	void SDLWindow::Close()
	{
		m_isOpen = false;
	}

	void SDLWindow::Shutdown()
	{
		if (m_window)
		{
			SDL_DestroyWindow(m_window);
			m_window = nullptr;
		}

		SDL_Quit();
		m_isOpen = false;
	}

	void* SDLWindow::GetNativeWindow() const
	{
		return static_cast<void*>(m_window);
	}
}