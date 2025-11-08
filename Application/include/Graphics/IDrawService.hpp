#pragma once

#include <utility>

namespace PixelPad::Core
namespace PixelPad::Application
{
    struct MouseButtonEvent;
    enum class ToolType;
    class CanvasViewport;

    class IDrawService
    {
    public:
        virtual void SetTool(const PixelPad::Core::ToolType& toolType) = 0;
        virtual void ProcessDrawInput(const MouseButtonEvent& mouseButtonEvent, CanvasViewport& canvasViewport) = 0;
        virtual void ClearCanvas() = 0;
        virtual void ResizeCanvas(int width, int height) = 0;
        virtual std::pair<int, int> GetCanvasSize() const = 0;
        virtual void SaveCanvasState() = 0;
        virtual void LoadCanvasState() = 0;
    };
}