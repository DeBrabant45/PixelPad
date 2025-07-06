#include "Tools/LineTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Core
{
	LineTool::LineTool(Canvas& canvas) :
		m_canvas(canvas),
		m_lastXCoordinate(-1),
		m_lastYCoordinate(-1)
	{

	}

	void LineTool::Reset()
	{
		m_lastXCoordinate = -1;
		m_lastYCoordinate = -1;
	}

	void LineTool::Draw(const DrawCommand& command)
	{
		// Capture the starting point on first press
		if (command.IsPressed && m_lastXCoordinate == -1 && m_lastYCoordinate == -1)
		{
			m_lastXCoordinate = command.X;
			m_lastYCoordinate = command.Y;
			return;
		}

		// On release, draw from the stored press point
		if (!command.IsPressed && m_lastXCoordinate >= 0 && m_lastYCoordinate >= 0)
		{
			m_canvas.DrawLine(m_lastXCoordinate, m_lastYCoordinate, command.X, command.Y, command.Color);
			Reset();
		}
	}

}