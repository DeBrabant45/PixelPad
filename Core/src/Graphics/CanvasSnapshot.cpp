#include "Graphics/CanvasSnapshot.hpp"

namespace PixelPad::Core
{
	CanvasSnapshot::CanvasSnapshot(int width, int height, std::vector<int> pixels) :
		m_width{ width },
		m_height{ height },
		m_pixels{ std::move(pixels) }
	{

	}

	int CanvasSnapshot::GetWidth() const
	{
		return m_width;
	}

	int CanvasSnapshot::GetHeight() const
	{
		return m_height;
	}

	const std::vector<int>& CanvasSnapshot::GetPixels() const
	{
		return m_pixels;
	}
}