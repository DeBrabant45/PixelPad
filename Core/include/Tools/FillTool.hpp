#pragma once 

#include "Tools/ITool.hpp"
#include "Graphics/Canvas.hpp"

namespace PixelPad::Core
{
	class FillTool : public ITool 
	{
	public:
		FillTool(Canvas& canvas);
		~FillTool() override = default;
		void Reset() override;
		void Draw(const DrawCommand& command) override;

	private:
		Canvas& m_canvas;
	};
}