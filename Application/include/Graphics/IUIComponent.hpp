#pragma once

#include "Graphics/IRenderable.hpp"
#include "Graphics/ISprite.hpp"
#include "Geometries/Transform.hpp"

#include <memory>

namespace PixelPad::Application
{
	class IUIComponent : public IRenderable
	{
	public:
		virtual ~IUIComponent() = default;
		virtual void SetSprite(std::unique_ptr<ISprite> sprite) = 0;
		virtual const PixelPad::Core::Transform& GetTransform() const = 0;
	};
}