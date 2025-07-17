#pragma once

namespace PixelPad::Application
{
	class IInput
	{
	public:
		virtual ~IInput() = default;
		virtual void PollEvents() = 0;
	};
}