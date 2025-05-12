#pragma once

#include <vector>

namespace PixelPad::Core
{
	class Canvas;

	class CanvasSnapshot
	{
	public:
		CanvasSnapshot(int width, int height, std::vector<int> pixels);
		~CanvasSnapshot() = default;
		int GetWidth() const;
		int GetHeight() const;
		const std::vector<int>& GetPixels() const;
		void ApplyTo(Canvas& canvas) const;

	private:
		int m_width;
		int m_height;
		std::vector<int> m_pixels;
	};
}