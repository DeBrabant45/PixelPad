#pragma once

#include "Graphics/IRenderable.hpp"

namespace PixelPad::Application
{
	class IUIPanel : public IRenderable
	{
	public:
		virtual ~IUIPanel() = default;
	};
}