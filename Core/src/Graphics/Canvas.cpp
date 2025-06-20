#include "Graphics/Canvas.hpp"
#include <iostream>

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

	void Canvas::DrawPixel(int x, int y, int color)
	{
		if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		{
			std::cerr << "Warning: Attempted to draw pixel out of bounds at (" << x << ", " << y << ")\n";
			return;
		}

		m_canvas[y * m_width + x] = color;
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
		std::cout << "Canvas filled with color: " << color << std::endl;
	}

	int Canvas::GetPixel(int x, int y) const
	{
		if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		{
			std::cerr << "GetPixel: Coordinates out of bounds." << std::endl;
			return -1;
		}

		return m_canvas[y * m_width + x];
	}

	std::vector<int> Core::Canvas::GetPixels() const
	{
		return m_canvas;
	}
}