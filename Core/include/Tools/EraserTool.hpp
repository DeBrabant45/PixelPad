#pragma once 

#include "Tools/ITool.hpp"
#include "Graphics/Canvas.hpp"

namespace PixelPad::Core
{
	class EraserTool : public ITool
	{
	public:
		EraserTool(Canvas& canvas);
		~EraserTool() override = default;
		void Reset() override;
		void Draw(const DrawCommand& command) override;

	private:
		bool HasPreviousCoordinates() const;
		void DrawEraserLine(int startX, int startY, int endX, int endY);
		void DrawEraserCircle(int centerX, int centerY);

	private:
		Canvas& m_canvas;
		unsigned int m_eraseColor;
		int m_lastXCoordinate;
		int m_lastYCoordinate;
	};
}