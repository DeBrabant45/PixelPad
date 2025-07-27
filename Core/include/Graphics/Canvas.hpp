#pragma once

#include <vector>

namespace PixelPad::Core
{
	class Canvas
	{
	public:
		Canvas(int width, int height, uint32_t backgroundColor);
		~Canvas() = default;
		void Clear();
		void DrawPixel(int x, int y, int color);
		void DrawLine(int startX, int startY, int endX, int endY, int color);
		void DrawCircleFilled(int centerX, int centerY, int radius, int color);
		void DrawCircleOutline(int centerX, int centerY, int radius, int color);
		void DrawRectangle(int startX, int startY, int endX, int endY, int color);
		void DrawEllipse(int centerX, int centerY, int radiusX, int radiusY, int color);
		void Resize(int width, int height);
		void Fill(int color);
		void FloodFill(int startX, int startY, int fillColor);
		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }
		int GetPixel(int x, int y) const;
		std::vector<int> GetPixels() const;

	private:
		inline bool IsInBounds(int x, int y) const { return (x >= 0 && x < m_width && y >= 0 && y < m_height); }

	private:
		std::vector<int> m_canvas;
		int m_width{ 0 };
		int m_height{ 0 };
		uint32_t m_backgroundColor{ 0xFFFFFFFF };
	};
}