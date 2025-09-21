#pragma once

#include "Tools/ITool.hpp"
#include "Graphics/Canvas.hpp"

namespace PixelPad::Core
{ 
	class EllipseTool : public ITool
	{
	public:
		EllipseTool(Canvas& canvas);
		~EllipseTool() override = default;
		void Reset() override;
		void Draw(const DrawCommand& command) override;

	private:
		Canvas& m_canvas;
		int m_startXCoordinate;
		int m_startYCoordinate;
		bool m_isDrawing;
	};
}