#pragma once 

#include "Tools/ITool.hpp"
#include "Graphics/Canvas.hpp"

namespace PixelPad::Core
{
	class LineTool : public ITool 
	{
	public:
		LineTool(Canvas& canvas);
		~LineTool() override = default;
		void Reset() override;
		void Draw(const DrawCommand& command) override;

	private:
		Canvas& m_canvas;
		int m_lastXCoordinate;
		int m_lastYCoordinate;
	};
}