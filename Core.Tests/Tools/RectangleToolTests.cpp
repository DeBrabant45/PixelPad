#include <gtest/gtest.h>
#include "Graphics/Canvas.hpp"
#include "Tools/RectangleTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Tests::Core
{
	TEST(RectangleToolTests, Draw_ShouldDrawRectangleBorder_WhenPressedAndReleased)
	{
		const int end = 5;
		const int expectedColor = 150;
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Core::RectangleTool rectangleTool{ canvas };

		for (int i = 0; i <= end; i++)
		{
			rectangleTool.Draw({ i, 5, expectedColor, true });
		}
		rectangleTool.Draw({ 5, 5, expectedColor, false });

		for (int x = 0; x <= end; x++)
		{
			EXPECT_EQ(canvas.GetPixel(x, 5), expectedColor);
		}
	}

	TEST(RectangleToolTests, Draw_ShouldDrawSinglePixelRectangle_WhenPressedAndReleasedAtSamePoint)
	{
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Core::RectangleTool rectangleTool{ canvas };

		rectangleTool.Draw({ 5, 5, 200, true });
		rectangleTool.Draw({ 5, 5, 200, false });

		EXPECT_EQ(canvas.GetPixel(5, 5), 200);
	}

	TEST(RectangleToolTests, Draw_ShouldDrawCorrectRectangle_WhenDraggedFromTopLeftToBottomRight)
	{
		const int startX = 0;
		const int startY = 0;
		const int endX = 5;
		const int endY = 5;
		const int expectedColor = 150;

		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Core::RectangleTool rectangleTool{ canvas };

		rectangleTool.Draw({ startX, startY, expectedColor, true });
		rectangleTool.Draw({ endX, endY, expectedColor, false });

		for (int x = startX; x <= endX; ++x)
		{
			EXPECT_EQ(canvas.GetPixel(x, startY), expectedColor);
			EXPECT_EQ(canvas.GetPixel(x, endY), expectedColor);
		}

		for (int y = startY; y <= endY; ++y)
		{
			EXPECT_EQ(canvas.GetPixel(startX, y), expectedColor);
			EXPECT_EQ(canvas.GetPixel(endX, y), expectedColor);
		}
	}

	TEST(RectangleToolTests, Draw_ShouldDrawCorrectRectangle_WhenDraggedFromBottomRightToTopLeft)
	{
		const int startX = 5;
		const int startY = 5;
		const int endX = 0;
		const int endY = 0;
		const int expectedColor = 150;

		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Core::RectangleTool rectangleTool{ canvas };

		rectangleTool.Draw({ startX, startY, expectedColor, true });
		rectangleTool.Draw({ endX, endY, expectedColor, false });

		for (int x = endX; x <= startX; ++x)
		{
			EXPECT_EQ(canvas.GetPixel(x, startY), expectedColor);
			EXPECT_EQ(canvas.GetPixel(x, endY), expectedColor);
		}

		for (int y = endY; y <= startY; ++y)
		{
			EXPECT_EQ(canvas.GetPixel(startX, y), expectedColor);
			EXPECT_EQ(canvas.GetPixel(endX, y), expectedColor);
		}
	}

	TEST(RectangleToolTests, Draw_ShouldResetStartPoint_WhenDrawCompletes)
	{
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Core::RectangleTool rectangleTool{ canvas };

		rectangleTool.Draw({ 2, 2, 100, true });
		rectangleTool.Draw({ 3, 3, 100, false });

		rectangleTool.Draw({ 6, 6, 112, true });
		rectangleTool.Draw({ 7, 7, 112, false });

		EXPECT_EQ(canvas.GetPixel(2, 2), 100);
		EXPECT_EQ(canvas.GetPixel(3, 3), 100);
		EXPECT_EQ(canvas.GetPixel(6, 6), 112);
		EXPECT_EQ(canvas.GetPixel(7, 7), 112);
	}

	TEST(RectangleToolTests, Draw_ShouldNotDraw_WhenCoordinatesAreCompletelyOutsideCanvas)
	{
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Core::RectangleTool rectangleTool{ canvas };

		rectangleTool.Draw({ -20, -20, 50, true });
		rectangleTool.Draw({ -15, -15, 50, false });

		for (int y = 0; y < 10; ++y)
		{
			for (int x = 0; x < 10; ++x)
			{
				EXPECT_EQ(canvas.GetPixel(x, y), 0);
			}
		}
	}

	TEST(RectangleToolTests, Draw_ShouldDrawBorderAndIgnoreOutOfBounds_WhenPressedAndReleasedOutsideOfCanvas)
	{
		const int expectedColor = 150;
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Core::RectangleTool rectangleTool{ canvas };

		rectangleTool.Draw({ 8, 8, expectedColor, true });
		rectangleTool.Draw({ 12, 12, expectedColor, false });

		EXPECT_EQ(canvas.GetPixel(8, 8), expectedColor);
		EXPECT_EQ(canvas.GetPixel(9, 8), expectedColor); 
		EXPECT_EQ(canvas.GetPixel(8, 9), expectedColor); 

		EXPECT_EQ(canvas.GetPixel(9, 9), 0);

		EXPECT_EQ(canvas.GetPixel(10, 10), -1);
		EXPECT_EQ(canvas.GetPixel(11, 11), -1);
		EXPECT_EQ(canvas.GetPixel(12, 12), -1);
	}

	TEST(RectangleToolTests, Draw_ShouldNotDraw_WhenReleasedWithoutPriorPress)
	{
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Core::RectangleTool rectangleTool{ canvas };

		rectangleTool.Draw({ 5, 5, 100, false });

		EXPECT_EQ(canvas.GetPixel(5, 5), 0);
	}

	TEST(RectangleToolTests, Draw_ShouldNotDraw_WhenOnlyPressedAndHeld)
	{
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Core::RectangleTool rectangleTool{ canvas };

		rectangleTool.Draw({ 5, 5, 100, true });

		EXPECT_EQ(canvas.GetPixel(5, 5), 0);
	}
}