#pragma once

namespace PixelPad::Application
{
	class IRenderer;

	class IRenderable
	{
	public:
		virtual ~IRenderable() = default;
		virtual void Render(IRenderer& renderer) = 0;
	};
}