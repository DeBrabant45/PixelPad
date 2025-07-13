#include <gtest/gtest.h>
#include "Graphics/Canvas.hpp"
#include "Tools/FillTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Tests::Core
{
	TEST(FillToolTests, Draw_ShouldFillPixelColor_WhenPressed)
	{
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Core::FillTool fillTool{ canvas };
		PixelPad::Core::DrawCommand drawCommand{ 2, 3, 42, true };

		fillTool.Draw(drawCommand);

		EXPECT_EQ(canvas.GetPixel(drawCommand.X, drawCommand.Y), drawCommand.Color);
	}

	TEST(FillToolTests, Draw_ShouldNotFillPixelColor_WhenNotPressed)
	{
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Core::FillTool fillTool{ canvas };
		PixelPad::Core::DrawCommand drawCommand{ 2, 3, 42, false };

		fillTool.Draw(drawCommand);

		EXPECT_EQ(canvas.GetPixel(drawCommand.X, drawCommand.Y), 0);
	}
}