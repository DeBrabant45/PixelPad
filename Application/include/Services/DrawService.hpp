#pragma once

#include "CanvasModel.hpp"
#include "IDrawService.hpp"

namespace Application
{
	class DrawService : public IDrawService
	{
	public:
		DrawService(Core::CanvasModel& canvasModel);
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

	private:
		Core::CanvasModel& m_canvasModel;
	};
}