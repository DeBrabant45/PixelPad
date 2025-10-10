#include "Tools/EllipseTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Core
{
	EllipseTool::EllipseTool(Canvas& canvas) :
		m_canvas(canvas), 
		m_startXCoordinate(-1), 
		m_startYCoordinate(-1),
		m_isDrawing(false)
	{

	}

	void EllipseTool::Reset()
	{
		m_startXCoordinate = -1;
		m_startYCoordinate = -1;
		m_isDrawing = false;
	}

	void EllipseTool::Draw(const DrawCommand& command)
	{
		if (command.IsPressed && !m_isDrawing)
		{
			m_startXCoordinate = command.X;
			m_startYCoordinate = command.Y;
			m_isDrawing = true;
			return;
		}

		if (!command.IsPressed && m_isDrawing)
		{
			auto centerX = (m_startXCoordinate + command.X) / 2;
			auto centerY = (m_startYCoordinate + command.Y) / 2;
			auto radiusX = abs(command.X - m_startXCoordinate) / 2;
			auto radiusY = abs(command.Y - m_startYCoordinate) / 2;
			m_canvas.DrawEllipse(centerX, centerY, radiusX, radiusY, command.Color);
			Reset();
		}
	}
}