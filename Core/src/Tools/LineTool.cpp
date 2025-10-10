#include "Tools/LineTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Core
{
	LineTool::LineTool(Canvas& canvas) :
		m_canvas(canvas),
		m_lastXCoordinate(-1),
		m_lastYCoordinate(-1),
		m_isDrawing(false)
	{

	}

	void LineTool::Reset()
	{
		m_lastXCoordinate = -1;
		m_lastYCoordinate = -1;
		m_isDrawing = false;
	}

	void LineTool::Draw(const DrawCommand& command)
	{
		if (command.IsPressed && !m_isDrawing)
		{
			m_lastXCoordinate = command.X;
			m_lastYCoordinate = command.Y;
			m_isDrawing = true;
			return;
		}

		if (!command.IsPressed && m_isDrawing)
		{
			m_canvas.DrawLine(m_lastXCoordinate, m_lastYCoordinate, command.X, command.Y, command.Color);
			Reset();
		}
	}
}