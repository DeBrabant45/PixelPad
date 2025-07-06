#include "Tools/PencilTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Core
{
	PencilTool::PencilTool(Canvas& canvas):
		m_canvas(canvas),
		m_lastXCoordinate(-1),
		m_lastYCoordinate(-1)
	{

	}

	void PencilTool::Reset()
	{
		m_lastXCoordinate = -1;
		m_lastYCoordinate = -1;
	}

	void PencilTool::Draw(const DrawCommand& command)
	{
		if (command.IsPressed)
		{
			if (m_lastXCoordinate >= 0 && m_lastYCoordinate >= 0)
			{
				m_canvas.DrawLine(m_lastXCoordinate, m_lastYCoordinate, command.X, command.Y, command.Color);
			}
			else
			{
				m_canvas.DrawPixel(command.X, command.Y, command.Color);
			}
			m_lastXCoordinate = command.X;
			m_lastYCoordinate = command.Y;
		}
		else
		{
			Reset();
		}
	}
}