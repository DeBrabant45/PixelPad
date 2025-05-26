#pragma once

namespace PixelPad::Infrastructure
{
	class IWindow
	{
	public:
        virtual ~IWindow() = default;
        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;
        virtual void Resize(int newWidth, int newHeight) = 0;
        virtual bool IsOpen() const = 0;
        virtual void Close() = 0;
        virtual void Shutdown() = 0;
        virtual void* GetNativeWindow() const = 0;
	};
}