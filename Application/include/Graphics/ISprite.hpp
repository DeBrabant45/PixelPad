#pragma once
#include <memory>

namespace PixelPad::Application
{
	class ITexture;

	class ISprite
	{
	public:
		virtual ~ISprite() = default;
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual int GetXCoordinate() const = 0;
		virtual int GetYCoordinate() const = 0;
		virtual std::shared_ptr<ITexture> GetTexture() = 0;
	};
}
