#include "Tools/FillTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Core
{
	FillTool::FillTool(Canvas& canvas) :
		m_canvas(canvas)
	{

	}

	void FillTool::Reset()
	{

	}

	void FillTool::Draw(const DrawCommand& command)
	{
		if (!command.IsPressed)
			return;

		m_canvas.FloodFill(command.X, command.Y, command.Color);
	}
}