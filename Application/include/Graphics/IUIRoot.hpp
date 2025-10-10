#pragma once

#include "Graphics/IRenderable.hpp"

namespace PixelPad::Application
{
	class IUIRoot : public IRenderable
	{
	public:
		virtual ~IUIRoot() = default;
	};
}