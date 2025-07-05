#pragma once

#include "Graphics/Canvas.hpp"
#include "Graphics/CanvasSnapshot.hpp"
#include "IDrawService.hpp"
#include "Enums/ToolType.hpp"
#include "Tools/PencilTool.hpp"
#include "Tools/LineTool.hpp"
#include "Tools/EraserTool.hpp"
#include "Tools/ITool.hpp"

#include <memory>

namespace PixelPad::Application
{
	class DrawService : public IDrawService
	{
	public:
		DrawService(PixelPad::Core::Canvas & canvas);
		~DrawService() = default;

        void DrawPixel(int x, int y, int color) override;
        void DrawLine(int startX, int startY, int endX, int endY, int color) override;
        void ResizeCanvas(int width, int height) override;
        void FillCanvas(int color) override;
        void ClearCanvas() override;
        std::pair<int, int> GetCanvasSize() const override;
        int GetPixel(int x, int y) const override;
        void SaveCanvasState() override;
        void LoadCanvasState() override;
        void ProcessDrawInput(const MouseButtonEvent& mouseButtonEvent) override;
        void SelectTool(const ToolType& toolType) override;

	private:
        PixelPad::Core::Canvas& m_canvas;
        std::unique_ptr<PixelPad::Core::CanvasSnapshot> m_canvasSnapshot;
        PixelPad::Core::PencilTool m_pencilTool;
		PixelPad::Core::LineTool m_lineTool;
        PixelPad::Core::EraserTool m_eraserTool;
		PixelPad::Core::ITool* m_currentTool;
	};
}