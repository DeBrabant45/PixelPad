#include "Tools/EraserTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Core
{
	EraserTool::EraserTool(Canvas& canvas) :
		m_canvas(canvas),
		m_lastXCoordinate(-1),
		m_lastYCoordinate(-1)
	{

	}

	void EraserTool::Reset()
	{

	}

	void EraserTool::Draw(const DrawCommand& command)
	{

	}
}