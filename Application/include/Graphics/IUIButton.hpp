#pragma once

#include "Graphics/IRenderable.hpp"

#include <functional>

namespace PixelPad::Application
{
	struct Transform
	{
		int x;
		int y;
		int width;
		int height;
	};

	class IUIButton : public IRenderable
	{
	public:
		virtual ~IUIButton() = default;
		virtual void OnClick(const std::function<void()>& callback) = 0;
		virtual void HandleClick(int clickX, int clickY) = 0;
		virtual Transform GetTransform() const = 0;
	};
}