#pragma once

#include <utility>

namespace PixelPad::Application
{
    class IDrawService
    {
    public:
        virtual void DrawPixel(int x, int y, int color) = 0;
        virtual void DrawLine(int startX, int startY, int endX, int endY, int color) = 0;
        virtual void ResizeCanvas(int width, int height) = 0;
        virtual void FillCanvas(int color) = 0;
        virtual void ClearCanvas() = 0;
        virtual std::pair<int, int> GetCanvasSize() const = 0;
        virtual int GetPixel(int x, int y) const = 0;

        virtual void SaveCanvasState() = 0;
        virtual void LoadCanvasState() = 0;
    };
}
