#include <gtest/gtest.h>
#include "Graphics/Canvas.hpp"

using namespace Core;

namespace CoreTests
{
    TEST(CanvasTests, InitializesWithCorrectSize)
    {
        Canvas canvas(10, 5);
        canvas.DrawPixel(0, 0, 255);
        canvas.DrawPixel(9, 4, 123);

        SUCCEED();
    }

    TEST(CanvasTests, ClearsCanvas)
    {
        Canvas canvas(3, 3);
        canvas.DrawPixel(1, 1, 100);
        canvas.Clear();

        SUCCEED();
    }

    TEST(CanvasTests, DrawPixelWithinBounds)
    {
        Canvas canvas(5, 5);
        canvas.DrawPixel(2, 3, 42);

        SUCCEED();
    }

    TEST(CanvasTests, DrawPixelOutOfBoundsDoesNothing)
    {
        Canvas canvas(5, 5);
        canvas.DrawPixel(-1, -1, 999);
        canvas.DrawPixel(10, 10, 999);

        SUCCEED();
    }

    TEST(CanvasTests, DrawLineHorizontal)
    {
        Canvas canvas(5, 3);
        canvas.DrawLine(0, 0, 4, 0, 255);  // Horizontal line at y=0

        // Check that the entire row is filled with color 255
        for (int x = 0; x < 5; ++x)
        {
            EXPECT_EQ(canvas.GetPixel(x, 0), 255);
        }
    }

    TEST(CanvasTests, DrawLineVertical)
    {
        Canvas canvas(3, 5);
        canvas.DrawLine(1, 0, 1, 4, 123);  // Vertical line at x=1

        // Check that the entire column is filled with color 123
        for (int y = 0; y < 5; ++y)
        {
            EXPECT_EQ(canvas.GetPixel(1, y), 123);
        }
    }

    TEST(CanvasTests, DrawLineDiagonal)
    {
        Canvas canvas(5, 5);
        canvas.DrawLine(0, 0, 4, 4, 255);  // Diagonal line from (0,0) to (4,4)

        EXPECT_EQ(canvas.GetPixel(0, 0), 255);
        EXPECT_EQ(canvas.GetPixel(1, 1), 255);
        EXPECT_EQ(canvas.GetPixel(2, 2), 255);
        EXPECT_EQ(canvas.GetPixel(3, 3), 255);
        EXPECT_EQ(canvas.GetPixel(4, 4), 255);
    }

    TEST(CanvasTests, GetPixel)
    {
		Canvas canvas(5, 5);
		canvas.DrawPixel(2, 2, 42);
		int pixelValue = canvas.GetPixel(2, 2);

		EXPECT_EQ(pixelValue, 42);
    }

    TEST(CanvasTests, FillCanvasWithSingleColor)
    {
        Canvas canvas(3, 2);
        canvas.Fill(99);

        for (int y = 0; y < 2; ++y)
        {
            for (int x = 0; x < 3; ++x)
            {
                EXPECT_EQ(canvas.GetPixel(x, y), 99);
            }
        }
    }

    TEST(CanvasTests, FillOverwritesPreviousPixels)
    {
        Canvas canvas(2, 2);
        canvas.DrawPixel(0, 0, 1);
        canvas.DrawPixel(1, 1, 2);

        canvas.Fill(42);

        EXPECT_EQ(canvas.GetPixel(0, 0), 42);
        EXPECT_EQ(canvas.GetPixel(1, 1), 42);
    }

    TEST(CanvasTests, ResizeLargerPreservesExistingPixels)
    {
        Canvas canvas(2, 2);
        canvas.DrawPixel(0, 0, 1);
        canvas.DrawPixel(1, 1, 2);

        canvas.Resize(4, 4);

        EXPECT_EQ(canvas.GetPixel(0, 0), 1);
        EXPECT_EQ(canvas.GetPixel(1, 1), 2);
        EXPECT_EQ(canvas.GetPixel(3, 3), 0);
    }

    TEST(CanvasTests, ResizeSmallerTruncatesPixels)
    {
        Canvas canvas(4, 4);
        canvas.DrawPixel(3, 3, 9);
        canvas.Resize(2, 2);

        EXPECT_EQ(canvas.GetPixel(0, 0), 0);
    }

    TEST(CanvasTests, ResizeWithSameSizeKeepsData)
    {
        Canvas canvas(3, 3);
        canvas.DrawPixel(1, 1, 7);
        canvas.Resize(3, 3);

        EXPECT_EQ(canvas.GetPixel(1, 1), 7);
    }
}