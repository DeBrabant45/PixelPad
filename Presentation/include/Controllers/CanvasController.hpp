#pragma once

#include "Graphics/Canvas.hpp"
#include "Services/DrawService.hpp"
#include "Services/IDrawService.hpp"
#include "Buses/EventBus.hpp"

namespace PixelPad::Presentation
{
	class CanvasController
	{
	public:
		CanvasController(PixelPad::Core::Canvas& canvas, Application::IDrawService& drawService, PixelPad::Infrastructure::EventBus& eventBus);
		~CanvasController();        
		void SetBackgroundColor(int color);
		void DrawPixel(int x, int y, int color);
		void DrawLine(int x1, int y1, int x2, int y2, int color);
		void Resize(int width, int height);
		void Clear();
		void Fill();

	private:
		void RegisterEventHandlers();
		void UnregisterEventHandlers();

	private:
		Core::Canvas& m_canvas;
		Application::IDrawService& m_drawService;
		int m_backgroundColor = 0xFFFFFFFF;
		PixelPad::Infrastructure::EventBus& m_eventBus;
		PixelPad::Infrastructure::EventBus::SubscriptionToken m_mouseEventToken;

		// For Testing draw line eventing
		int m_prevX{-1};
		int m_prevY{ -1 };
	};
}