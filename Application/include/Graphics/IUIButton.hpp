#pragma once

#include "Graphics/IRenderable.hpp"

#include <string>

namespace PixelPad::Application
{
	struct Transform
	{
		int x;
		int y;
		int width;
		int height;
	};

	struct ClickResult
	{
		std::string ButtonId;
	};

	class IUIButton : public IRenderable
	{
	public:
		virtual ~IUIButton() = default;
		virtual void OnClick(int clickX, int clickY) = 0;
		virtual Transform GetTransform() const = 0;
	};
}