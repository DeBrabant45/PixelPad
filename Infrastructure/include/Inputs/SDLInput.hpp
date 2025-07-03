#pragma once

#include "Inputs/IInput.hpp"
#include "Buses/EventBus.hpp"

struct SDL_MouseButtonEvent;
struct SDL_MouseMotionEvent;

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
		void ProcessMouseButtonEvent(unsigned int type, SDL_MouseButtonEvent& button); 
		void ProcessMouseMotionEvent(unsigned int type, SDL_MouseMotionEvent& motion);

	private:
		EventBus& m_eventBus;
	};
}