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

    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;
        virtual void ClearScreen() = 0;
        virtual void Render(const PixelPad::Core::Canvas& canvas) = 0;
        virtual void DrawTexture(PixelPad::Application::ITexture* texture, int x, int y, int width, int height) = 0;
        virtual void Present() = 0;
        virtual void Shutdown() = 0;
    };
}