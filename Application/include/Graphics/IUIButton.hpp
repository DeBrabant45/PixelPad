#pragma once

#include "Graphics/IRenderable.hpp"
#include "Geometries/Transform.hpp"

#include <string>

namespace PixelPad::Application
{
	struct ClickResult
	{
		std::string ButtonId;
	};

	class IUIButton : public IRenderable
	{
	public:
		virtual ~IUIButton() = default;
		virtual void OnClick(int clickX, int clickY) = 0;
		virtual PixelPad::Core::Transform GetTransform() const = 0;
	};
}