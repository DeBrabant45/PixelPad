#pragma once

namespace Infrastructure
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