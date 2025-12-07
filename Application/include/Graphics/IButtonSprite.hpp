#pragma once

#include "Graphics/ISprite.hpp"

namespace PixelPad::Application
{
	enum class ButtonState
	{
		UnClicked = 0,
		Clicked = 1,
	};

	class IButtonSprite : public virtual ISprite
	{
	public:
		virtual ~IButtonSprite() = default;
		virtual void SetState(ButtonState state) = 0;
	};
}