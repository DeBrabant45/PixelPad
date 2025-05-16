#pragma once

#include "Windows/IWindow.hpp"

struct SDL_Window;

namespace PixelPad::Infrastructure
{
	class SDLWindow : public IWindow
	{
	public:
		SDLWindow(int width, int height, const char* title);
		~SDLWindow() override;
		int GetWidth() const override;
		int GetHeight() const override;
		void Resize(int newWidth, int newHeight) override;
		bool IsOpen() const override;
		void PollEvents() override;
		void Shutdown() override;
		void* GetNativeWindow() const override;

	private:
		SDL_Window* m_window{ nullptr };
		int m_width{ 800 };
		int m_height{ 600 };
		bool m_isOpen{ true };
	};
}