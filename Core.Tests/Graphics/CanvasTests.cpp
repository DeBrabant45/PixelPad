#include <gtest/gtest.h>
#include "Graphics/Canvas.hpp"

namespace PixelPad::Tests::Core
{
    TEST(CanvasTests, Constructor_ShouldInitializeCanvasWithCorrectSize)
    {
        PixelPad::Core::Canvas canvas(10, 5);
        canvas.DrawPixel(0, 0, 255);
        canvas.DrawPixel(9, 4, 123);

        SUCCEED();
    }

    TEST(CanvasTests, Clear_ShouldSetAllPixelsToZero)
    {
        PixelPad::Core::Canvas canvas(3, 3);
        canvas.DrawPixel(1, 1, 100);
        canvas.Clear();

        SUCCEED();
    }

    TEST(CanvasTests, DrawPixel_ShouldSetPixelValue_WhenCoordinatesAreInBounds)
    {
        PixelPad::Core::Canvas canvas(5, 5);
        canvas.DrawPixel(2, 3, 42);

        SUCCEED();
    }

    TEST(CanvasTests, DrawPixel_ShouldDoNothing_WhenCoordinatesAreOutOfBounds)
    {
        PixelPad::Core::Canvas canvas(5, 5);
        canvas.DrawPixel(-1, -1, 999);
        canvas.DrawPixel(10, 10, 999);

        SUCCEED();
    }

    TEST(CanvasTests, DrawLine_ShouldDrawHorizontalLine_WhenStartAndEndYAreSame)
    {
        PixelPad::Core::Canvas canvas(5, 3);
        canvas.DrawLine(0, 0, 4, 0, 255);

        for (int x = 0; x < 5; ++x)
        {
            EXPECT_EQ(canvas.GetPixel(x, 0), 255);
        }
    }

    TEST(CanvasTests, DrawLine_ShouldDrawVerticalLine_WhenStartAndEndXAreSame)
    {
        PixelPad::Core::Canvas canvas(3, 5);
        canvas.DrawLine(1, 0, 1, 4, 123);

        for (int y = 0; y < 5; ++y)
        {
            EXPECT_EQ(canvas.GetPixel(1, y), 123);
        }
    }

    TEST(CanvasTests, DrawLine_ShouldDrawDiagonalLine_WhenStartAndEndFormDiagonal)
    {
        PixelPad::Core::Canvas canvas(5, 5);
        canvas.DrawLine(0, 0, 4, 4, 255);

        EXPECT_EQ(canvas.GetPixel(0, 0), 255);
        EXPECT_EQ(canvas.GetPixel(1, 1), 255);
        EXPECT_EQ(canvas.GetPixel(2, 2), 255);
        EXPECT_EQ(canvas.GetPixel(3, 3), 255);
        EXPECT_EQ(canvas.GetPixel(4, 4), 255);
    }

    TEST(CanvasTests, GetPixel_ShouldReturnCorrectValue_WhenPixelWasSet)
    {
        PixelPad::Core::Canvas canvas(5, 5);
        canvas.DrawPixel(2, 2, 42);
        int pixelValue = canvas.GetPixel(2, 2);

        EXPECT_EQ(pixelValue, 42);
    }

    TEST(CanvasTests, Fill_ShouldSetAllPixelsToSpecifiedColor)
    {
        PixelPad::Core::Canvas canvas(3, 2);
        canvas.Fill(99);

        for (int y = 0; y < 2; ++y)
        {
            for (int x = 0; x < 3; ++x)
            {
                EXPECT_EQ(canvas.GetPixel(x, y), 99);
            }
        }
    }

    TEST(CanvasTests, Fill_ShouldOverwriteAllExistingPixelValues)
    {
        PixelPad::Core::Canvas canvas(2, 2);
        canvas.DrawPixel(0, 0, 1);
        canvas.DrawPixel(1, 1, 2);

        canvas.Fill(42);

        EXPECT_EQ(canvas.GetPixel(0, 0), 42);
        EXPECT_EQ(canvas.GetPixel(1, 1), 42);
    }

    TEST(CanvasTests, Resize_ShouldPreserveExistingPixels_WhenNewSizeIsLarger)
    {
        PixelPad::Core::Canvas canvas(2, 2);
        canvas.DrawPixel(0, 0, 1);
        canvas.DrawPixel(1, 1, 2);

        canvas.Resize(4, 4);

        EXPECT_EQ(canvas.GetPixel(0, 0), 1);
        EXPECT_EQ(canvas.GetPixel(1, 1), 2);
        EXPECT_EQ(canvas.GetPixel(3, 3), 0);
    }

    TEST(CanvasTests, Resize_ShouldTruncatePixelData_WhenNewSizeIsSmaller)
    {
        PixelPad::Core::Canvas canvas(4, 4);
        canvas.DrawPixel(3, 3, 9);
        canvas.Resize(2, 2);

        EXPECT_EQ(canvas.GetPixel(0, 0), 0);
    }

    TEST(CanvasTests, Resize_ShouldPreserveAllPixels_WhenNewSizeIsSame)
    {
        PixelPad::Core::Canvas canvas(3, 3);
        canvas.DrawPixel(1, 1, 7);
        canvas.Resize(3, 3);

        EXPECT_EQ(canvas.GetPixel(1, 1), 7);
    }
}