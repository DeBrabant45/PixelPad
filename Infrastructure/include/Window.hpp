#pragma once

namespace PixelPad::Infrastructure
{
	class Window
	{
	public:
		Window() = default;
		~Window() = default;
		void Create();
		void Destroy();
	};
}