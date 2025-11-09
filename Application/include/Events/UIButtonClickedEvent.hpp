#pragma once

namespace PixelPad::Application
{
	template<typename T>
	struct UIButtonClickedEvent
	{
		T Value;

		UIButtonClickedEvent() = default;

		explicit UIButtonClickedEvent(const T& value)
		{
			Value = value;
		}
	};
}