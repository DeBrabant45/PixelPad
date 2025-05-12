#include "Graphics/CanvasSnapshot.hpp"
#include "Graphics/Canvas.hpp"

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

	void Core::CanvasSnapshot::ApplyTo(Canvas& canvas) const
	{
		canvas.Resize(GetWidth(), GetHeight());

		const auto& pixels = GetPixels();
		for (int y = 0; y < GetHeight(); ++y)
		{
			for (int x = 0; x < GetWidth(); ++x)
			{
				int index = y * GetWidth() + x;
				canvas.DrawPixel(x, y, pixels[index]);
			}
		}
	}
}