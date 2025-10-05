#include "Graphics/Sprite.hpp"

namespace PixelPad::Application
{
	Sprite::Sprite(const PixelPad::Core::Transform& transform, std::shared_ptr<ITexture> texture) :
		m_transform(transform),
		Texture(texture)
	{

	}

	int Sprite::GetWidth() const
	{
		return m_transform.Width;
	}

	int Sprite::GetHeight() const
	{
		return m_transform.Height;
	}

	int Sprite::GetXCoordinate() const
	{
		return m_transform.X;
	}

	int Sprite::GetYCoordinate() const
	{
		return m_transform.Y;
	}

	int Sprite::GetZCoordinate() const
	{
		return m_transform.Z;
	}

	std::shared_ptr<ITexture> Sprite::GetTexture()
	{
		return Texture;
	}
}