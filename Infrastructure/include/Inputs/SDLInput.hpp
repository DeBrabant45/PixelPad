#pragma once

#include "Inputs/IInput.hpp"
#include "Buses/EventBus.hpp"

namespace PixelPad::Infrastructure
{
	class SDLInput : public IInput
	{
	public:
		SDLInput(EventBus& eventBus);
		~SDLInput() override = default;
		void PollEvents() override;

	private:
		EventBus& m_eventBus;
	};
}