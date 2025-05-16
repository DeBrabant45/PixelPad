#pragma once

#include "Windows/IWindow.hpp"
#include "Buses/EventBus.hpp"

struct SDL_Window;

namespace PixelPad::Infrastructure
{
	class SDLWindow : public IWindow
	{
	public:
		SDLWindow(int width, int height, const char* title, EventBus& bus);
		~SDLWindow() override;
		int GetWidth() const override;
		int GetHeight() const override;
		void Resize(int newWidth, int newHeight) override;
		bool IsOpen() const override;
		void Close() override;
		void Shutdown() override;
		void* GetNativeWindow() const override;

	private:
		void CreateSDLWindow(int width, int height, const char* title);
		void RegisterEventHandlers();

	private:
		SDL_Window* m_window{ nullptr };
		int m_width{ 800 };
		int m_height{ 600 };
		bool m_isOpen{ true };
		EventBus& m_eventBus;
	};
}