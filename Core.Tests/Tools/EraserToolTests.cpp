#include <gtest/gtest.h>
#include "Graphics/Canvas.hpp"
#include "Tools/EraserTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Tests::Core
{
	TEST(EraserToolTests, Draw_ShouldSetCorrectPixelColor)
	{
		const int expectedColor = 0xFFFFFFFF;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Core::EraserTool eraserTool{ canvas };
		PixelPad::Core::DrawCommand drawCommand{ 2, 3, 42, true };

		eraserTool.Draw(drawCommand);

		EXPECT_EQ(canvas.GetPixel(drawCommand.X, drawCommand.Y), expectedColor);
	}

	TEST(EraserToolTests, Draw_ShouldNoThrowError_WhenOutOfBounds)
	{
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Core::EraserTool eraserTool{ canvas };
		PixelPad::Core::DrawCommand drawCommand1{ -1, -1, 123, true };
		PixelPad::Core::DrawCommand drawCommand2{ 10, 10, 25, true };

		EXPECT_NO_THROW(eraserTool.Draw(drawCommand1));
		EXPECT_NO_THROW(eraserTool.Draw(drawCommand2));
	}

	TEST(EraserToolTests, Draw_ShouldUpdateMultiplePixels_WhenMultipleCallsAreMade)
	{
		const int expectedColor = 0xFFFFFFFF;
		PixelPad::Core::Canvas canvas{ 6, 6, 0 };
		PixelPad::Core::EraserTool eraserTool{ canvas };

		eraserTool.Draw({ 1, 1, 200, true });
		eraserTool.Draw({ 1, 1, 200, false });

		eraserTool.Draw({ 2, 2, 190, true });
		eraserTool.Draw({ 2, 2, 190, false });

		eraserTool.Draw({ 3, 3, 18, true });
		eraserTool.Draw({ 3, 3, 18, false });

		EXPECT_EQ(canvas.GetPixel(1, 1), expectedColor);
		EXPECT_EQ(canvas.GetPixel(2, 2), expectedColor);
		EXPECT_EQ(canvas.GetPixel(3, 3), expectedColor);
	}

	TEST(EraserToolTests, Draw_ShouldNotThrowError_WhenNegativeCoordinatesArePassed)
	{
		PixelPad::Core::Canvas canvas{ 6, 6, 0 };
		PixelPad::Core::EraserTool eraserTool{ canvas };
		PixelPad::Core::DrawCommand drawCommand{ -1, -1, 240, true };

		EXPECT_NO_THROW(eraserTool.Draw(drawCommand));
	}

	TEST(EraserToolTests, Draw_ShouldOverwritePixelColor_WhenPixelIsAlreadyColored)
	{
		const int expectedColor = 0xFFFFFFFF;
		PixelPad::Core::Canvas canvas{ 6, 6, 100 };
		PixelPad::Core::EraserTool eraserTool{ canvas };
		PixelPad::Core::DrawCommand drawCommand1{ 1, 1, 2, true };
		PixelPad::Core::DrawCommand drawCommand2{ 1, 1, 100, true };

		eraserTool.Draw(drawCommand1);
		eraserTool.Draw(drawCommand2);

		EXPECT_EQ(canvas.GetPixel(drawCommand2.X, drawCommand2.Y), expectedColor);
	}

	TEST(EraserToolTests, Draw_ShouldSetPixelColor_WhenMinEdgeCoordinatesAreUsed)
	{
		const int expectedColor = 0xFFFFFFFF;
		PixelPad::Core::Canvas canvas{ 1, 1, 0 };
		PixelPad::Core::EraserTool eraserTool{ canvas };
		PixelPad::Core::DrawCommand drawCommand{ 0, 0, 200, true };

		eraserTool.Draw(drawCommand);

		EXPECT_EQ(canvas.GetPixel(drawCommand.X, drawCommand.Y), expectedColor);
	}

	TEST(EraserToolTests, Draw_ShouldSetPixelColor_WhenMaxEdgeCoordinatesAreUsed)
	{
		const int expectedColor = 0xFFFFFFFF;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Core::EraserTool eraserTool{ canvas };
		PixelPad::Core::DrawCommand drawCommand{ 4, 4, 155, true };

		eraserTool.Draw(drawCommand);

		EXPECT_EQ(canvas.GetPixel(drawCommand.X, drawCommand.Y), expectedColor);
	}

	TEST(EraserToolTests, Draw_ShouldEraseInterpolatedPath_WhenDraggedAcrossCanvas)
	{
		const int expectedColor = 0xFFFFFFFF;
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Core::EraserTool eraserTool{ canvas };

		eraserTool.Draw({ 1, 1, 123, true });
		eraserTool.Draw({ 5, 5, 123, true });
		eraserTool.Draw({ 5, 5, 123, false });

		EXPECT_EQ(canvas.GetPixel(1, 1), expectedColor);
		EXPECT_EQ(canvas.GetPixel(3, 3), expectedColor);
		EXPECT_EQ(canvas.GetPixel(5, 5), expectedColor);
	}

	TEST(EraserToolTests, Draw_ShouldResetLastCoordinates_WhenMouseReleased)
	{
		const int expectedColor = 0xFFFFFFFF;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Core::EraserTool eraserTool{ canvas };

		eraserTool.Draw({ 2, 2, 100, true });
		eraserTool.Draw({ 3, 3, 100, false });

		eraserTool.Draw({ 4, 4, 100, true });

		EXPECT_EQ(canvas.GetPixel(4, 4), expectedColor);
	}
}