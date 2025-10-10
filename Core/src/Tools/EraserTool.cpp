#include "Tools/EraserTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Core
{
	EraserTool::EraserTool(Canvas& canvas) :
		m_canvas(canvas),
		m_eraseColor(0xFFFFFFFF),
		m_lastXCoordinate(-1),
		m_lastYCoordinate(-1),
		m_isDrawing(false)
	{

	}

	void EraserTool::Reset()
	{
		m_lastXCoordinate = -1;
		m_lastYCoordinate = -1;
		m_isDrawing = false;
	}

	void EraserTool::Draw(const DrawCommand& command)
	{
		if (!command.IsPressed)
		{
			Reset();
			return;
		}

		if (m_isDrawing)
		{
			DrawEraserLine(m_lastXCoordinate, m_lastYCoordinate, command.X, command.Y);
		}
		else
		{
			DrawEraserCircle(command.X, command.Y);
			m_isDrawing = true;
		}

		m_lastXCoordinate = command.X;
		m_lastYCoordinate = command.Y;
	}

	void EraserTool::DrawEraserLine(int startX, int startY, int endX, int endY)
	{
		int deltaX = endX - startX;
		int deltaY = endY - startY;
		int interpolationSteps = std::max(std::abs(deltaX), std::abs(deltaY));

		for (int step = 0; step <= interpolationSteps; step++)
		{
			float progress = step / static_cast<float>(interpolationSteps);
			int interpolatedX = static_cast<int>(startX + progress * deltaX);
			int interpolatedY = static_cast<int>(startY + progress * deltaY);
			DrawEraserCircle(interpolatedX, interpolatedY);
		}
	}

	void EraserTool::DrawEraserCircle(int centerX, int centerY)
	{
		m_canvas.DrawCircleFilled(centerX, centerY, 10, m_eraseColor);
	}
}