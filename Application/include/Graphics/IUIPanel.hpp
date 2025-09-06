#pragma once

#include "Graphics/IRenderable.hpp"

namespace PixelPad::Application
{
	class IUIPanel : public IRenderable
	{
	public:
		virtual ~IUIPanel() = default;
		virtual void HandleClick(int clickX, int clickY) = 0;
	};
}