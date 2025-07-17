#pragma once

#include <utility>

namespace PixelPad::Application
{
    struct MouseButtonEvent;
    enum class ToolType;

    class IDrawService
    {
    public:
        virtual void SelectTool(const ToolType& toolType) = 0;
        virtual void ProcessDrawInput(const MouseButtonEvent& mouseButtonEvent) = 0;
        virtual void ClearCanvas() = 0;
        virtual void ResizeCanvas(int width, int height) = 0;
        virtual std::pair<int, int> GetCanvasSize() const = 0;
        virtual void SaveCanvasState() = 0;
        virtual void LoadCanvasState() = 0;
    };
}