#pragma once

namespace PixelPad::Core
{
	struct DrawCommand;

	class ITool
	{
	public:
		virtual ~ITool() = 0;
		virtual void Reset() = 0;
		virtual void Draw(const DrawCommand& command) = 0;
	};

	inline ITool::~ITool() = default;
}