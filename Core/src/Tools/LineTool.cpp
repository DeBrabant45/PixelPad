#include "Tools/LineTool.hpp"

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

	void LineTool::Draw(int x, int y, bool isPressed)
	{
		if (m_lastXCoordinate < 0 || m_lastYCoordinate < 0)
		{
			m_lastXCoordinate = x;
			m_lastYCoordinate = y;
		}

		if (!isPressed)
		{
			m_canvas.DrawLine(m_lastXCoordinate, m_lastYCoordinate, x, y, 0xFF000000);
			m_lastXCoordinate = x;
			m_lastYCoordinate = y;
		}
	}
}