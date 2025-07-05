#pragma once

namespace PixelPad::Core
{
	class ITool
	{
	public:
		virtual ~ITool() = 0;
		virtual void Reset() = 0;
		virtual void Draw(int x, int y, bool isPressed) = 0;
	};

	inline ITool::~ITool() = default;
}