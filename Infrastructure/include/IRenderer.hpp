#pragma once

#include <cstdint>
#include <vector>

namespace PixelPad::Core
{
	class Canvas;
}

namespace PixelPad::Infrastructure
{
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        // Clears the screen with a default or custom background color
        virtual void ClearScreen() = 0;

        // Renders the canvas content to the screen (using the window + renderer)
        virtual void Render(const PixelPad::Core::Canvas& canvas) = 0;

        // Presents the rendered frame to the screen (swaps buffers)
        virtual void Present() = 0;

        // Optionally allows resizing the renderer or canvas
        virtual void Resize(int newWidth, int newHeight) = 0;

        // Shuts down the renderer and releases resources
        virtual void Shutdown() = 0;
    };
}