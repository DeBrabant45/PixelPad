#pragma once

#include <vector>

namespace PixelPad::Core
{
	class Canvas
	{
	public:
		Canvas(int width, int height);
		~Canvas() = default;
		void Clear();
		void DrawPixel(int x, int y, int color);
		void DrawLine(int startX, int startY, int endX, int endY, int color);
		void Resize(int width, int height);
		void Fill(int color);
		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }
		int GetPixel(int x, int y) const;
		std::vector<int> GetPixels() const;

	private:
		int m_width{ 0 };
		int m_height{ 0 };
		std::vector<int> m_canvas;
	};
}