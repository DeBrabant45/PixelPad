#pragma once

namespace PixelPad::Core
{
	class Canvas;
}

namespace PixelPad::Application
{
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;
        virtual void ClearScreen() = 0;
        virtual void Render(const PixelPad::Core::Canvas& canvas) = 0;
        virtual void Present() = 0;
        virtual void Shutdown() = 0;
    };
}