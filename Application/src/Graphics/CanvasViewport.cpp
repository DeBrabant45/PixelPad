#include "Graphics/CanvasViewport.hpp"

namespace PixelPad::Application
{
	CanvasViewport::CanvasViewport(int width, int height, int xOffset, int yOffset) :
		m_width(width),
		m_height(height),
		m_xOffset(xOffset),
		m_yOffset(yOffset)
	{

	}

	bool CanvasViewport::Contains(int x, int y) const
	{
		return (x >= m_xOffset && x < m_xOffset + m_width &&
			y >= m_yOffset && y < m_yOffset + m_height);
	}

	std::pair<int, int> CanvasViewport::ToLocal(int x, int y) const
	{
		return { x - m_xOffset, y - m_yOffset };
	}
}