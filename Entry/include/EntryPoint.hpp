#pragma once

#include "Services/DrawService.hpp" 
#include "Renderer.hpp"
#include "CanvasModel.hpp"

namespace Entry
{
	class EntryPoint
	{
	public:
		EntryPoint();
		~EntryPoint();
		void Run();

	private:
		void Initialize();
		void Shutdown();

	private:
		Infrastructure::Renderer m_renderer;
		Core::CanvasModel m_canvasModel;
	};
}