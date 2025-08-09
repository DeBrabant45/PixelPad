#pragma once

#include "Graphics/Canvas.hpp"
#include "Graphics/CanvasSnapshot.hpp"
#include "IDrawService.hpp"
#include "Enums/ToolType.hpp"
#include "Tools/PencilTool.hpp"
#include "Tools/LineTool.hpp"
#include "Tools/EraserTool.hpp"
#include "Tools/FillTool.hpp"
#include "Tools/RectangleTool.hpp"
#include "Tools/EllipseTool.hpp"
#include "Tools/ITool.hpp"

#include <memory>

namespace PixelPad::Application
{
	class DrawService : public IDrawService
	{
	public:
		DrawService(PixelPad::Core::Canvas & canvas);
		~DrawService() = default;
		void SelectTool(const ToolType& toolType) override;
        void ProcessDrawInput(const MouseButtonEvent& mouseButtonEvent) override;
		void ClearCanvas() override;
		void ResizeCanvas(int width, int height) override;
		std::pair<int, int> GetCanvasSize() const override;
		void SaveCanvasState() override;
		void LoadCanvasState() override;

	private:
        PixelPad::Core::Canvas& m_canvas;
        PixelPad::Core::PencilTool m_pencilTool;
		PixelPad::Core::LineTool m_lineTool;
        PixelPad::Core::EraserTool m_eraserTool;
		PixelPad::Core::FillTool m_fillTool;
		PixelPad::Core::RectangleTool m_rectangleTool;
		PixelPad::Core::EllipseTool m_ellipseTool;
		PixelPad::Core::ITool* m_currentTool;
		std::unique_ptr<PixelPad::Core::CanvasSnapshot> m_canvasSnapshot;
	};
}