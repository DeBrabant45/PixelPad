#include "Tools/RectangleTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Core
{
	RectangleTool::RectangleTool(Canvas& canvas) :
		m_canvas(canvas),
		m_lastXCoordinate(-1),
		m_lastYCoordinate(-1),
		m_isDrawing(false)
	{

	}

	void RectangleTool::Reset()
	{
		m_lastXCoordinate = -1;
		m_lastYCoordinate = -1;
		m_isDrawing = false;
	}

	void RectangleTool::Draw(const DrawCommand& command)
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
			m_canvas.DrawRectangle(m_lastXCoordinate, m_lastYCoordinate, command.X, command.Y, command.Color);
			Reset();
		}
	}
}