#include "Graphics/Sprite.hpp"

namespace PixelPad::Application
{
	Sprite::Sprite(int width, int height, int xCoordinate, int yCoordinate, int zOrder, std::shared_ptr<ITexture> texture) :
		m_width(width),
		m_height(height),
		m_xCoordinate(xCoordinate),
		m_yCoordinate(yCoordinate),
		m_zOrder(zOrder),
		m_texture(texture)
	{

	}

	int Sprite::GetWidth() const
	{
		return m_width;
	}

	int Sprite::GetHeight() const
	{
		return m_height;
	}

	int Sprite::GetXCoordinate() const
	{
		return m_xCoordinate;
	}

	int Sprite::GetYCoordinate() const
	{
		return m_yCoordinate;
	}

	int Sprite::GetZOrder() const
	{
		return m_zOrder;
	}

	std::shared_ptr<ITexture> Sprite::GetTexture()
	{
		return m_texture;
	}
}