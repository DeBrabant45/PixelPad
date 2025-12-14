#pragma once

#include "Windows/IWindow.hpp"
#include "Paths/AssetPathProvider.hpp"

struct SDL_Window;

namespace PixelPad::Infrastructure
{
	class SDLWindow : public PixelPad::Application::IWindow
	{
	public:
		SDLWindow(int width, int height, const char* title, bool resizable, const IPathProvider& pathProvider);
		~SDLWindow() override;
		void Shutdown() override;
		int GetWidth() const override;
		int GetHeight() const override;
		void Resize(int newWidth, int newHeight) override;
		bool IsOpen() const override;
		void Close() override;
		void* GetNativeWindow() const override;

	private:
		void CreateSDLWindow(int width, int height, const char* title, bool resizable);
		void SetWindowIcon();

	private:
		SDL_Window* m_window{ nullptr };
		int m_width{ 800 };
		int m_height{ 600 };
		bool m_isOpen{ true };
		const IPathProvider& m_pathProvider;
	};
}