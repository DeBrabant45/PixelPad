#pragma once

#include <memory>
#include <string>

namespace PixelPad::Core
{
	class Canvas;
}

namespace PixelPad::Application
{
	class ITexture;
    class CanvasViewport;
    class ISprite;

    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;
        virtual void ClearScreen() = 0;
        virtual void Render(const PixelPad::Core::Canvas& canvas, CanvasViewport& canvasViewport) = 0;
        virtual void Render(PixelPad::Application::ISprite* sprite) = 0;
        virtual void Present() = 0;
        virtual void Shutdown() = 0;
    };
}