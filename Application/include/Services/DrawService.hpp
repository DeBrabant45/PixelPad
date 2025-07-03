#pragma once

#include "Graphics/Canvas.hpp"
#include "Graphics/CanvasSnapshot.hpp"
#include "IDrawService.hpp"
#include "Enums/ToolType.hpp"

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
        void SetToolType(const ToolType& toolType) override;

    private:
        void DrawWithPencil(const MouseButtonEvent& mouseButtonEvent);

	private:
        PixelPad::Core::Canvas& m_canvas;
        std::unique_ptr<PixelPad::Core::CanvasSnapshot> m_canvasSnapshot;
		ToolType m_currentToolType;
        int m_lastXCoordinate;
		int m_lastYCoordinate;
	};
}