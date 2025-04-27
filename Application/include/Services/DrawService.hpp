#pragma once

#include "Graphics/Canvas.hpp"
#include "IDrawService.hpp"

namespace Application
{
	class DrawService : public IDrawService
	{
	public:
		DrawService(Core::Canvas& canvas);
		~DrawService() = default;

        void DrawPixel(int x, int y, int color) override; // Done
        void DrawLine(int startX, int startY, int endX, int endY, int color) override; 
        void ResizeCanvas(int width, int height) override; // Done
        void FillCanvas(int color) override; // Done
        void ClearCanvas() override; // Done
        std::pair<int, int> GetCanvasSize() const override; // Done
        int GetPixel(int x, int y) const override; // Done

        void SaveCanvasState() override;
        void LoadCanvasState() override;

	private:
		Core::Canvas& m_canvas;
	};
}