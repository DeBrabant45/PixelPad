#pragma once

namespace PixelPad::Infrastructure
{
	class IInput
	{
	public:
		virtual ~IInput() = default;
		virtual void PollEvents() = 0;
	};
}