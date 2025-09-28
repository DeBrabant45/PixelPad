#pragma once

#include <utility>

namespace PixelPad::Application
{
	class CanvasViewport
	{
	public:
		CanvasViewport(int width, int height, int xOffset, int yOffset);
		~CanvasViewport() = default;
		bool Contains(int x, int y) const;
		std::pair<int, int> ToLocal(int x, int y) const;
		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }
		int GetXOffset() const { return m_xOffset; }
		int GetYOffset() const { return m_yOffset; }

	private:
		int m_width;
		int m_height;
		int m_xOffset;
		int m_yOffset;
	};
}