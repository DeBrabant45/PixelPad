#include <gtest/gtest.h>
#include "Graphics/Canvas.hpp"
#include "Tools/LineTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Tests::Core
{
    TEST(LineToolTests, Draw_ShouldRenderStraightHorizontalLine_WhenPressedAndReleased)
    {
        const int end = 5;
        const int expectedColor = 170;
        PixelPad::Core::Canvas canvas{ 10, 10, 0 };
        PixelPad::Core::LineTool lineTool{ canvas };

        for (int x = 0; x <= end; ++x)
        {
            lineTool.Draw({ x, 5, expectedColor, true });
        }
        lineTool.Draw({ 5, 5, expectedColor, false });

        for (int x = 0; x <= end; ++x)
        {
            EXPECT_EQ(canvas.GetPixel(x, 5), expectedColor);
        }
    }

    TEST(LineToolTests, Draw_ShouldRenderStraightVerticalLine_WhenPressedAndReleased)
    {
        const int end = 5;
        const int expectedColor = 170;
        PixelPad::Core::Canvas canvas{ 10, 10, 0 };
        PixelPad::Core::LineTool lineTool{ canvas };

        for (int y = 0; y <= end; ++y)
        {
            lineTool.Draw({ 5, y, expectedColor, true });
        }
        lineTool.Draw({ end, end, expectedColor, false });

        for (int y = 0; y <= end; ++y)
        {
            EXPECT_EQ(canvas.GetPixel(end, y), expectedColor);
        }
    }

    TEST(LineToolTests, Draw_ShouldRenderDiagonalLine_WhenPressedAndReleased)
    {
        const int end = 5;
        const int expectedColor = 170;
        PixelPad::Core::Canvas canvas{ 10, 10, 0 };
        PixelPad::Core::LineTool lineTool{ canvas };

        for (int i = 0; i <= end; ++i)
        {
            lineTool.Draw({ i, i, expectedColor, true });
        }
        lineTool.Draw({ end, end, expectedColor, false });

        for (int i = 0; i <= end; ++i)
        {
            EXPECT_EQ(canvas.GetPixel(i, i), expectedColor);
        }
    }

    TEST(LineToolTests, Draw_ShouldRenderLineInNegativeDirection_WhenPressedAndReleased)
    {
        constexpr int start = 8;
        constexpr int end = 0;
        const int expectedColor = 160;
        PixelPad::Core::Canvas canvas{ 12, 12, 0 };
        PixelPad::Core::LineTool lineTool{ canvas };

        for (int i = start; i > end; --i)
        {
            lineTool.Draw({ i, i, expectedColor, true });
        }
        lineTool.Draw({ end, end, expectedColor, false });

        for (int i = end; i <= start; ++i)
        {
            EXPECT_EQ(canvas.GetPixel(i, i), expectedColor);
        }
    }

    TEST(LineToolTests, Draw_ShouldRenderSinglePixel_WhenPressedAndReleased)
    {
        const int expectedColor = 150;
        PixelPad::Core::Canvas canvas{ 10, 10, 0 };
        PixelPad::Core::LineTool lineTool{ canvas };

        lineTool.Draw({ 5, 5, expectedColor, true});
		lineTool.Draw({ 5, 5, expectedColor, false });

        EXPECT_EQ(canvas.GetPixel(5, 5), expectedColor);
    }

    TEST(LineToolTests, Draw_ShouldNoThrowError_WhenOutOfBounds)
    {
        const int expectedColor = 150;
        PixelPad::Core::Canvas canvas{ 10, 10, 0 };
        PixelPad::Core::LineTool lineTool{ canvas };

        EXPECT_NO_THROW(lineTool.Draw({ -1, -1, expectedColor, true }));
        EXPECT_NO_THROW(lineTool.Draw({ 15, 15, expectedColor, false }));
    }

    TEST(LineToolTests, Draw_ShouldOverWriteExistingColor_WhenOverlappingExistingPixels)
    {
        const int expectedColor = 200;
        PixelPad::Core::Canvas canvas{ 10, 10, 0 };
        PixelPad::Core::LineTool lineTool{ canvas };

        lineTool.Draw({ 5, 5, 100, true });
        lineTool.Draw({ 5, 5, 100, false });
        lineTool.Draw({ 5, 5, expectedColor, true });
        lineTool.Draw({ 5, 5, expectedColor, false });

        EXPECT_EQ(canvas.GetPixel(5, 5), expectedColor);
    }

    TEST(LineToolTests, Draw_ShouldNotAlterCanvas_WhenZeroLengthLine)
    {
        const int expectedColor = 20;
        PixelPad::Core::Canvas canvas{ 10, 10, 0 };
        PixelPad::Core::LineTool lineTool{ canvas };

        lineTool.Draw({ 5, 5, expectedColor, true });
        lineTool.Draw({ 5, 5, expectedColor, false });
        lineTool.Draw({ 0, 0, 120, true });
        lineTool.Draw({ 0, 0, 120, false });

        EXPECT_EQ(canvas.GetPixel(5, 5), expectedColor);
    }

    TEST(LineToolTests, Draw_ShouldOnlyRenderWithinBounds_WhenLongLineBeyondCanvas)
    {
        const int expectedColor = 100;
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Core::LineTool lineTool{ canvas };

        lineTool.Draw({ 0, 0, expectedColor, true });
        lineTool.Draw({ 99, 99, expectedColor, false });

        EXPECT_EQ(canvas.GetPixel(1, 1), expectedColor);
        EXPECT_EQ(canvas.GetPixel(2, 2), expectedColor);
        EXPECT_EQ(canvas.GetPixel(3, 3), expectedColor);
        EXPECT_EQ(canvas.GetPixel(4, 4), expectedColor);
        EXPECT_EQ(canvas.GetPixel(5, 5), -1);
        EXPECT_EQ(canvas.GetPixel(6, 6), -1);
    }

    TEST(LineToolTests, Draw_ShouldNotOverFlow_WhenSmallCanvasLine)
    {
        const int expectedColor = 100;
        PixelPad::Core::Canvas canvas{ 2, 2, 0 };
        PixelPad::Core::LineTool lineTool{ canvas };

        lineTool.Draw({ 0, 0, expectedColor, true});
        lineTool.Draw({ 1, 1, expectedColor, false });

        EXPECT_EQ(canvas.GetPixel(0, 0), expectedColor);
    }

    TEST(LineToolTests, Draw_ShouldRenderDiagonalLineAcrossLargeCanvas_WhenPressedAndReleased)
    {
        const int expectedColor = 100;
        PixelPad::Core::Canvas canvas{ 100, 100, 0 };
        PixelPad::Core::LineTool lineTool{ canvas };

        lineTool.Draw({ 0, 0, expectedColor, true });
        lineTool.Draw({ 99, 99, expectedColor, false });

        EXPECT_EQ(canvas.GetPixel(50, 50), expectedColor);
    }

    TEST(LineToolTests, Draw_ShouldRenderCollinearOverlappingLinesCorrectly)
    {
        const int expectedColor = 120;
        PixelPad::Core::Canvas canvas{ 10, 10, 0 };
        PixelPad::Core::LineTool lineTool{ canvas };

        lineTool.Draw({ 0, 0, expectedColor, true });
        lineTool.Draw({ 5, 9, expectedColor, false });

        lineTool.Draw({ 2, 0, expectedColor, true });
        lineTool.Draw({ 7, 9, expectedColor, false });

        for (int i = 0; i <= 5; ++i)
        {
            int x = i;
            int y = (i * 9) / 5;
            if (x >= 0 && x < 10 && y >= 0 && y < 10)
            {
                EXPECT_EQ(canvas.GetPixel(x, y), expectedColor);
            }
        }

        for (int i = 2; i <= 7; ++i)
        {
            int x = i;
            int y = (i * 9) / 5;
            if (x >= 0 && x < 10 && y >= 0 && y < 10)
            {
                EXPECT_EQ(canvas.GetPixel(x, y), expectedColor);
            }
        }
    }
}