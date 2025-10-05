#pragma once

#include "Graphics/ISprite.hpp"
#include "Geometries/Transform.hpp"

namespace PixelPad::Application
{
	class Sprite : public ISprite
	{
	public:
		Sprite(const PixelPad::Core::Transform& transform, std::shared_ptr<ITexture> texture);
		int GetWidth() const override;
		int GetHeight() const override;
		int GetXCoordinate() const override;
		int GetYCoordinate() const override;
		int GetZCoordinate() const override;
		std::shared_ptr<ITexture> GetTexture() override;

	protected:
		std::shared_ptr<ITexture> Texture;

	private:
		PixelPad::Core::Transform m_transform;
	};
}