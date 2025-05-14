#pragma once

#include "IWindow.hpp"

struct SDL_Window;

namespace PixelPad::Infrastructure
{
	class Window : public IWindow
	{
	public:
		Window(int width, int height, const char* title);
		~Window() override;
		int GetWidth() const override;
		int GetHeight() const override;
		void Resize(int newWidth, int newHeight) override;
		bool IsOpen() const override;
		void PollEvents() override;
		void Shutdown() override;
		SDL_Window* GetNativeWindow() const override;

	private:
		SDL_Window* m_window{ nullptr };
		int m_width{ 800 };
		int m_height{ 600 };
		bool m_isOpen{ true };
	};
}