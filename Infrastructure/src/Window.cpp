#include "Window.hpp"
#include <SDL3/SDL.h>
#include <iostream>

namespace PixelPad::Infrastructure
{
	Window::Window(int width, int height, const char* title) :
		m_width(width),
		m_height(height)
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

	Window::~Window()
	{
		Shutdown();
	}

	int Window::GetWidth() const
	{
		return m_width;
	}

	int Window::GetHeight() const
	{
		return m_height;
	}

	void Window::Resize(int newWidth, int newHeight)
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

	bool Window::IsOpen() const
	{
		return m_isOpen;
	}

	void Window::PollEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				m_isOpen = false;
			}
			else if (event.type == SDL_EVENT_WINDOW_RESIZED)
			{
				m_width = event.window.data1;
				m_height = event.window.data2;
			}
		}
	}

	void Window::Shutdown()
	{
		if (m_window)
		{
			SDL_DestroyWindow(m_window);
			m_window = nullptr;
		}

		SDL_Quit();
		m_isOpen = false;
	}

	SDL_Window* Window::GetNativeWindow() const
	{
		return m_window;
	}
}