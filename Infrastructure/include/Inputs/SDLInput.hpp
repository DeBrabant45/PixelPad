#pragma once

#include "Inputs/IInput.hpp"
#include "Buses/EventBus.hpp"

struct SDL_MouseButtonEvent;
struct SDL_MouseMotionEvent;
struct SDL_WindowEvent;
struct SDL_KeyboardEvent;

namespace PixelPad::Infrastructure
{
	class SDLInput : public IInput
	{
	public:
		SDLInput(EventBus& eventBus);
		~SDLInput() override = default;
		void PollEvents() override;

	private:
		void ProcessWindowCloseEvent(unsigned int type);
		void ProcessWindowResizeEvent(unsigned int type, const SDL_WindowEvent& window);
		void ProcessMouseButtonEvent(unsigned int type, const SDL_MouseButtonEvent& button); 
		void ProcessMouseMotionEvent(unsigned int type, const SDL_MouseMotionEvent& motion);
		void ProcessKeyboardEvent(unsigned int type, const SDL_KeyboardEvent& key);

	private:
		EventBus& m_eventBus;
	};
}