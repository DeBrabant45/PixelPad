#include "Tools/PencilTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Core
{
	PencilTool::PencilTool(Canvas& canvas):
		m_canvas(canvas),
		m_lastXCoordinate(-1),
		m_lastYCoordinate(-1),
		m_isDrawing(false)
	{

	}

	void PencilTool::Reset()
	{
		m_lastXCoordinate = -1;
		m_lastYCoordinate = -1;
		m_isDrawing = false;
	}

	void PencilTool::Draw(const DrawCommand& command)
	{
		if (!command.IsPressed)
		{
			Reset();
			return;
		}

		if (m_isDrawing)
		{
			m_canvas.DrawLine(m_lastXCoordinate, m_lastYCoordinate, command.X, command.Y, command.Color);
		}
		else
		{
			m_canvas.DrawPixel(command.X, command.Y, command.Color);
			m_isDrawing = true;
		}

		m_lastXCoordinate = command.X;
		m_lastYCoordinate = command.Y;
	}
}