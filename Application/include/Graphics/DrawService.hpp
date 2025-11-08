#pragma once

#include "Graphics/Canvas.hpp"
#include "Graphics/CanvasSnapshot.hpp"
#include "IDrawService.hpp"
#include "Tools/ITool.hpp"
#include "Tools/IToolbox.hpp"

#include <memory>

namespace PixelPad::Application
{
	class DrawService : public IDrawService
	{
	public:
		DrawService(PixelPad::Core::Canvas & canvas, PixelPad::Application::IToolbox& toolbox);
		~DrawService() = default;
		void SetTool(const PixelPad::Core::ToolType& toolType) override;
        void ProcessDrawInput(const MouseButtonEvent& mouseButtonEvent, CanvasViewport& canvasViewport) override;
		void ClearCanvas() override;
		void ResizeCanvas(int width, int height) override;
		std::pair<int, int> GetCanvasSize() const override;
		void SaveCanvasState() override;
		void LoadCanvasState() override;

	private:
        PixelPad::Core::Canvas& m_canvas;
		PixelPad::Application::IToolbox& m_toolbox;
		PixelPad::Core::ITool* m_currentTool;
		std::unique_ptr<PixelPad::Core::CanvasSnapshot> m_canvasSnapshot;
	};
}