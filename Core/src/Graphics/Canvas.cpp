#include "Graphics/Canvas.hpp"

#include <iostream>
#include <queue>
#include <utility>
#include <cmath>

namespace PixelPad::Core
{
	Canvas::Canvas(int width, int height, uint32_t backgroundColor) :
		m_width{ width },
		m_height{ height },
		m_backgroundColor{ backgroundColor },
		m_canvas(width * height, backgroundColor) 
	{

	}

	void Canvas::Clear()
	{
		if (m_canvas.empty())
			return;

		std::fill(m_canvas.begin(), m_canvas.end(), 0);
		std::cout << "Canvas cleared." << std::endl;
	}

	//Bresenham's Line Algorithm
	void Canvas::DrawLine(int startX, int startY, int endX, int endY, int color)
	{
		// Calculate the horizontal and vertical distances between the start and end points
		int deltaX = std::abs(endX - startX);  // Horizontal distance (x direction)
		int deltaY = std::abs(endY - startY);  // Vertical distance (y direction)

		// Determine the direction of movement for each axis (positive or negative)
		int stepXDirection = (startX < endX) ? 1 : -1;  // 1 if moving right, -1 if moving left
		int stepYDirection = (startY < endY) ? 1 : -1;  // 1 if moving down, -1 if moving up

		// Calculate the initial error term (distance from the ideal line)
		int errorTerm = deltaX - deltaY;

		// Loop to draw the line
		while (true)
		{
			// Draw the pixel at the current coordinates
			DrawPixel(startX, startY, color);

			// If we've reached the destination point, stop drawing the line
			if (startX == endX && startY == endY)
				break;

			// Double the error term for comparison (avoids using floating-point numbers)
			int doubleErrorTerm = errorTerm * 2;

			// Check if the error term suggests we need to move horizontally (X direction)
			if (doubleErrorTerm > -deltaY)
			{
				// Adjust the error term for moving horizontally
				errorTerm -= deltaY;

				// Move to the next point in the X direction
				startX += stepXDirection;
			}

			// Check if the error term suggests we need to move vertically (Y direction)
			if (doubleErrorTerm < deltaX)
			{
				// Adjust the error term for moving vertically
				errorTerm += deltaX;

				// Move to the next point in the Y direction
				startY += stepYDirection;
			}
		}
	}

	void Canvas::DrawCircleFilled(int centerX, int centerY, int radius, int color)
	{
		const int radiusSquared = radius * radius;
		for (int offSetY = -radius; offSetY <= radius; ++offSetY)
		{
			for (int offSetX = -radius; offSetX <= radius; ++offSetX)
			{
				int distanceSquared = offSetX * offSetX + offSetY * offSetY;
				if (distanceSquared <= radiusSquared)
				{
					int pixelX = centerX + offSetX;
					int pixelY = centerY + offSetY;

					DrawPixel(pixelX, pixelY, color);
				}
			}
		}
	}

	void Canvas::DrawCircleOutline(int centerX, int centerY, int radius, int color)
	{
		const float PI = 3.14159265358979323846f;
		const int segments = 64;
		for (int i = 0; i < segments; i++)
		{
			float angleRadians = 2.0f * PI * i / segments;
			int pixelX = static_cast<int>(std::round(centerX + radius * std::cos(angleRadians)));
			int pixelY = static_cast<int>(std::round(centerY + radius * std::sin(angleRadians)));

			DrawPixel(pixelX, pixelY, color);
		}
	}

	void Canvas::DrawRectangle(int startX, int startY, int endX, int endY, int color)
	{
		int topLeftX = std::min(startX, endX);
		int topLeftY = std::min(startY, endY);
		int width = std::abs(endX - startX) + 1;
		int height = std::abs(endY - startY) + 1;
		if (width <= 0 || height <= 0)
			return;

		int bottomRightX = topLeftX + width - 1;
		int bottomRightY = topLeftY + height - 1;

		// Top Horizontal Line
		for (int pixelX = topLeftX; pixelX <= bottomRightX; ++pixelX)
		{
			DrawPixel(pixelX, topLeftY, color);
		}

		// Bottom horizontal line
		for (int pixelX = topLeftX; pixelX <= bottomRightX; ++pixelX)
		{
			DrawPixel(pixelX, bottomRightY, color);
		}

		// Left vertical line
		for (int pixelY = topLeftY; pixelY <= bottomRightY; ++pixelY)
		{
			DrawPixel(topLeftX, pixelY, color);
		}

		// Right vertical line
		for (int pixelY = topLeftY; pixelY <= bottomRightY; ++pixelY)
		{
			DrawPixel(bottomRightX, pixelY, color);
		}
	}

	//Bresenham's Ellipse Algorithm
	void Canvas::DrawEllipse(int centerX, int centerY, int radiusX, int radiusY, int color)
	{
		if (radiusX <= 0 || radiusY <= 0)
			return;

		int horizontalOffset = 0;
		int verticalOffset = radiusY;

		int radiusXSquared = radiusX * radiusX;
		int radiusYSquared = radiusY * radiusY;
		int regionOneDecisionMaker = radiusYSquared - (radiusXSquared * radiusY) + (radiusXSquared / 4);

		DrawPixel(centerX, centerY + radiusY, color);
		DrawPixel(centerX, centerY - radiusY, color);
		DrawPixel(centerX - radiusX, centerY, color);
		DrawPixel(centerX + radiusX, centerY, color);

		while (2 * radiusYSquared * horizontalOffset < 2 * radiusXSquared * verticalOffset)
		{
			if (regionOneDecisionMaker < 0)
			{
				horizontalOffset++;
				regionOneDecisionMaker += 2 * radiusYSquared * horizontalOffset + radiusYSquared;
			}
			else
			{
				horizontalOffset++;
				verticalOffset--;
				regionOneDecisionMaker += 2 * radiusYSquared * horizontalOffset - 2 * radiusXSquared * verticalOffset + radiusYSquared;
			}

			DrawPixel(centerX + horizontalOffset, centerY + verticalOffset, color);
			DrawPixel(centerX - horizontalOffset, centerY + verticalOffset, color);
			DrawPixel(centerX + horizontalOffset, centerY - verticalOffset, color);
			DrawPixel(centerX - horizontalOffset, centerY - verticalOffset, color);
		}

		int regionTwoDecisionMaker = radiusYSquared * (horizontalOffset + 0.5F) * (horizontalOffset + 0.5F) 
			+ radiusXSquared * (verticalOffset - 1) * (verticalOffset - 1)
			- radiusXSquared * radiusYSquared;

		while (verticalOffset > 0)
		{
			if (regionTwoDecisionMaker > 0)
			{
				verticalOffset--;
				regionTwoDecisionMaker -= 2 * radiusXSquared * verticalOffset - radiusXSquared;
			}
			else
			{
				verticalOffset--;
				horizontalOffset++;
				regionTwoDecisionMaker += 2 * radiusYSquared * horizontalOffset - 2 * radiusXSquared * verticalOffset + radiusXSquared;
			}

			DrawPixel(centerX + horizontalOffset, centerY + verticalOffset, color);
			DrawPixel(centerX - horizontalOffset, centerY + verticalOffset, color);
			DrawPixel(centerX + horizontalOffset, centerY - verticalOffset, color);
			DrawPixel(centerX - horizontalOffset, centerY - verticalOffset, color);
		}
	}

	void Canvas::Resize(int width, int height)
	{
		if (m_width == width && m_height == height)
			return;

		auto newCanvas = std::vector<int>(width * height, m_backgroundColor);
		for (int y = 0; y < std::min(m_height, height); ++y)
		{
			for (int x = 0; x < std::min(m_width, width); ++x)
			{
				newCanvas[y * width + x] = m_canvas[y * m_width + x];
			}
		}

		m_canvas = std::move(newCanvas);
		m_width = width;
		m_height = height;

		std::cout << "Canvas resized to " << width << "x" << height << "." << std::endl;
	}

	void Canvas::Fill(int color)
	{
		if (m_canvas.empty())
		{
			std::cout << "Canvas is empty, cannot fill." << std::endl;
			return;
		}

		std::fill(m_canvas.begin(), m_canvas.end(), color);
	}

	// Iterative 4-directional scanline flood fill.
	// Fills all connected pixels matching the target color starting from (startX, startY).
	// Uses horizontal span scanning and a queue for vertical neighbors.
	// Avoids recursion and redundant pixel checks.
	void Canvas::FloodFill(int startX, int startY, int fillColor)
	{
		if (!IsInBounds(startX, startY))
			return;
		
		int targetColor = GetPixel(startX, startY);
		if (targetColor == fillColor)
			return;

		std::queue<std::pair<int, int>> pixelQueue;
		pixelQueue.push({ startX, startY });

		while (!pixelQueue.empty()) 
		{
			auto [currentX, currentY] = pixelQueue.front();
			pixelQueue.pop();

			int color = m_canvas[currentY * m_width + currentX];
			if (color != targetColor)
				continue;

			int leftX = currentX;
			while (leftX >= 0 && m_canvas[currentY * m_width + leftX] == targetColor)
			{
				--leftX;
			}
			++leftX;

			int rightX = currentX;
			while (rightX < m_width && m_canvas[currentY * m_width + rightX] == targetColor)
			{
				++rightX;
			}
			--rightX;

			for (int i = leftX; i <= rightX; ++i)
			{
				m_canvas[currentY * m_width + i] = fillColor;

				if (currentY > 0 && m_canvas[(currentY-1) * m_width + i] == targetColor)
				{
					pixelQueue.push({ i, currentY - 1 });
				}

				if (currentY < m_height -1 && m_canvas[(currentY + 1) * m_width + 1] == targetColor)
				{
					pixelQueue.push({ i, currentY + 1 });
				}
			}
		}
	}

	int Canvas::GetPixel(int x, int y) const
	{
		if (!IsInBounds(x, y))
			return -1;

		return m_canvas[y * m_width + x];
	}

	std::vector<int> Core::Canvas::GetPixels() const
	{
		return m_canvas;
	}
}