#pragma once

#include "Graphics/ISprite.hpp"

#include <memory>

namespace PixelPad::Application
{
	class Sprite : public ISprite
	{
	public:
		Sprite(int width, int height, int xCoordinate, int yCoordinate, std::shared_ptr<ITexture> texture);
		int GetWidth() const override;
		int GetHeight() const override;
		int GetXCoordinate() const override;
		int GetYCoordinate() const override;
		std::shared_ptr<ITexture> GetTexture() override;

	private:
		std::shared_ptr<ITexture> m_texture;
		int m_width;
		int m_height;
		int m_xCoordinate;
		int m_yCoordinate;
	};
}