#pragma once

#include "Inputs/IInput.hpp"
#include "Buses/EventBus.hpp"

struct SDL_MouseButtonEvent;

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

	private:
		EventBus& m_eventBus;
	};
}