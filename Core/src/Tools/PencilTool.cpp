#include "Tools/PencilTool.hpp"

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

	void PencilTool::Draw(int x, int y, bool isPressed)
	{
		if (isPressed)
		{
			if (m_lastXCoordinate >= 0 && m_lastYCoordinate >= 0)
			{
				m_canvas.DrawLine(m_lastXCoordinate, m_lastYCoordinate, x, y, 0xFF000000);
			}
			else
			{
				m_canvas.DrawPixel(x, y, 0xFF000000);
			}
			m_lastXCoordinate = x;
			m_lastYCoordinate = y;
		}
		else
		{
			Reset();
		}
	}
}