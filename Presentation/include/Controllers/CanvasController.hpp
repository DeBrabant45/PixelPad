#pragma once

#include "Graphics/Canvas.hpp"
#include "Services/DrawService.hpp"

namespace PixelPad::Presentation
{
	class CanvasController
	{
	public:
		CanvasController(PixelPad::Core::Canvas& canvas, Application::DrawService& drawService);
		~CanvasController() = default;        
		void SetBackgroundColor(int color);
		void DrawPixel(int x, int y, int color);
		void DrawLine(int x1, int y1, int x2, int y2, int color);
		void Clear();
		void Fill();

	private:
		Core::Canvas& m_canvas;
		Application::DrawService& m_drawService;
		int m_backgroundColor = 0xFFFFFFFF;
	};
}