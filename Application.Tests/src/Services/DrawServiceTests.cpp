#include <gtest/gtest.h>
#include "Services/DrawService.hpp"
#include "Graphics/canvas.hpp"

namespace PixelPad::Tests::Application
{
    TEST(DrawServiceTests, Constructor_DoesNotThrowAndCanvasIsCorrectSize)
    {
        PixelPad::Core::Canvas canvas{8, 6, 0};
        PixelPad::Application::DrawService drawService{ canvas };

        EXPECT_EQ(canvas.GetWidth(), 8);
        EXPECT_EQ(canvas.GetHeight(), 6);
    }

    TEST(DrawServiceTests, DrawPixel_SetsCorrectPixelColor)
    {
        int x = 2;
        int y = 3;
        int expectedPixelColor = 42;
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::DrawService drawService{ canvas };

        drawService.DrawPixel(x, y, expectedPixelColor);

        EXPECT_EQ(canvas.GetPixel(x, y), expectedPixelColor);
    }

    TEST(DrawServiceTests, DrawPixel_OutOfBounds_DoesNotThrow)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::DrawService drawService{ canvas };

        EXPECT_NO_THROW(drawService.DrawPixel(-1, -1, 123));
        EXPECT_NO_THROW(drawService.DrawPixel(10, 10, 255));
    }

    TEST(DrawServiceTests, DrawPixel_MultipleCalls_UpdateMultiplePixels)
    {
        PixelPad::Core::Canvas canvas{ 6, 6, 0 };
        PixelPad::Application::DrawService drawService{ canvas };

        drawService.DrawPixel(5, 5, 200);
        drawService.DrawPixel(2, 2, 190);
        drawService.DrawPixel(3, 3, 180);

        EXPECT_EQ(canvas.GetPixel(5, 5), 200);
        EXPECT_EQ(canvas.GetPixel(2, 2), 190);
        EXPECT_EQ(canvas.GetPixel(3, 3), 180);
    }

    TEST(DrawServiceTests, DrawPixel_NegativeCoordinates_DoesNotThrow)
    {
        PixelPad::Core::Canvas canvas{ 6, 6, 0 };
        PixelPad::Application::DrawService drawService{ canvas };

        EXPECT_NO_THROW(drawService.DrawPixel(-1, -1, 240));
    }

    TEST(DrawServiceTests, DrawPixel_ColorOverwrite_UpdatesPixelColor)
    {
        PixelPad::Core::Canvas canvas{ 6, 6, 0 };
        PixelPad::Application::DrawService drawService{ canvas };

        drawService.DrawPixel(1, 1, 255);
        drawService.DrawPixel(1, 1, 100);

        EXPECT_EQ(canvas.GetPixel(1, 1), 100);
    }

    TEST(DrawServiceTests, DrawPixel_MinEdgeCoordinates_SetsPixelColor)
    {
        PixelPad::Core::Canvas canvas{ 1, 1, 0 };
        PixelPad::Application::DrawService drawService{ canvas };

        drawService.DrawPixel(0, 0, 200);

        EXPECT_EQ(canvas.GetPixel(0, 0), 200);
    }

    TEST(DrawServiceTests, DrawPixel_MaxEdgeCoordinates_SetsPixelColor)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::DrawService drawService{ canvas };

        drawService.DrawPixel(4, 4, 155);

        EXPECT_EQ(canvas.GetPixel(4, 4), 155);
    }

    TEST(DrawServiceTests, ResizeCanvas_ChangesCanvasSizeCorrectly)
    {
        int expectedWidth = 10;
        int expectedHeight = 10;
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::DrawService drawService{ canvas };

        drawService.ResizeCanvas(expectedWidth, expectedHeight);

        EXPECT_EQ(canvas.GetWidth(), expectedWidth);
        EXPECT_EQ(canvas.GetHeight(), expectedHeight);
    }

    TEST(DrawServiceTests, ResizeCanvas_ShrinksCanvas_ClearsOrPreservesData)
    {
        PixelPad::Core::Canvas canvas{ 10, 10, 0 };
        PixelPad::Application::DrawService drawService{ canvas };

        drawService.ResizeCanvas(5, 5);
        
        EXPECT_EQ(canvas.GetPixel(10, 10), -1);
    }

    TEST(DrawServiceTests, ResizeCanvas_ExpandsCanvas_SetsNewPixelsToDefault)
    {
        int expectedWidth = 5;
        int expectedHeight = 5;
        int expectedPixelColor = 0;
        PixelPad::Core::Canvas canvas{ expectedWidth, expectedHeight, 0 };
        PixelPad::Application::DrawService drawService{ canvas };

        canvas.Fill(155);
        drawService.ResizeCanvas(7, 7);

        EXPECT_EQ(canvas.GetPixel(expectedWidth, expectedHeight), expectedPixelColor);
    }

    TEST(DrawServiceTests, ResizeCanvas_ZeroSize_HandlesGracefully)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		EXPECT_NO_THROW(drawService.ResizeCanvas(0, 0));
		EXPECT_EQ(canvas.GetWidth(), 0);
		EXPECT_EQ(canvas.GetHeight(), 0);
    }

    TEST(DrawServiceTests, ResizeCanvas_NegativeValues_DoesNotThrow)
    {
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		EXPECT_NO_THROW(drawService.ResizeCanvas(-5, -5));
    }

    TEST(DrawServiceTests, FillCanvas_SetsAllPixelsToColor)
    {
		int expectedPixelColor = 100;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.FillCanvas(expectedPixelColor);

		EXPECT_EQ(canvas.GetPixel(1, 1), expectedPixelColor);
    }

    TEST(DrawServiceTests, FillCanvas_WithNegativeColor_SetsAllPixel)
    {
		int expectedPixelColor = -155;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.FillCanvas(expectedPixelColor);

		EXPECT_EQ(canvas.GetPixel(1, 1), expectedPixelColor);
    }

    TEST(DrawServiceTests, FillCanvas_WithZero_SetsAllPixelsToZero)
    {
		int expectedPixelColor = 0;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.FillCanvas(expectedPixelColor);

		EXPECT_EQ(canvas.GetPixel(1, 1), expectedPixelColor);
    }

    TEST(DrawServiceTests, FillCanvas_AfterDrawingPixels_OverridesAllPixels)
    {
		int expectedFillColor = 200;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.DrawPixel(1, 1, 100);
		drawService.DrawPixel(2, 2, 150);
		drawService.FillCanvas(expectedFillColor);

		EXPECT_EQ(canvas.GetPixel(1, 1), expectedFillColor);
		EXPECT_EQ(canvas.GetPixel(2, 2), expectedFillColor);
    }

    TEST(DrawServiceTests, FillCanvas_WithZeroCanvas_DoesNotThrow)
    {
		int fillColor = 215;
		PixelPad::Core::Canvas canvas{ 0, 0, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		EXPECT_NO_THROW(drawService.FillCanvas(fillColor));
		EXPECT_EQ(canvas.GetPixel(0, 0), -1);
    }

    TEST(DrawServiceTests, ClearCanvas_ResetsAllPixelsToDefault)
    {
		int expectedPixelColor = 0;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		canvas.Fill(100);
		drawService.ClearCanvas();

		EXPECT_EQ(canvas.GetPixel(1, 1), expectedPixelColor);
		EXPECT_EQ(canvas.GetPixel(2, 2), expectedPixelColor);
		EXPECT_EQ(canvas.GetPixel(3, 3), expectedPixelColor);
		EXPECT_EQ(canvas.GetPixel(4, 4), expectedPixelColor);
    }

    TEST(DrawServiceTests, ClearCanvas_EmptyCanvas_DoesNotThrow)
    {
		PixelPad::Core::Canvas canvas{ 0, 0, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		EXPECT_NO_THROW(drawService.ClearCanvas());
    }

    TEST(DrawServiceTests, ClearCanvas_AfterResize_StillClearsAllPixels)
    {
        int expectedPixelColor = 0;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

        drawService.ResizeCanvas(3, 3);
		drawService.ClearCanvas();

		EXPECT_EQ(canvas.GetPixel(1, 1), expectedPixelColor);
		EXPECT_EQ(canvas.GetPixel(2, 2), expectedPixelColor);
    }

    TEST(DrawServiceTests, GetPixel_ReturnsCorrectValue_WhenPixelIsSet)
    {
		int expectedPixelColor = 123;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.DrawPixel(2, 2, expectedPixelColor);
		int actualPixelColor = drawService.GetPixel(2, 2);

		EXPECT_EQ(actualPixelColor, expectedPixelColor);
    }

    TEST(DrawServiceTests, GetPixel_DefaultValue_WhenPixelWasNotModified)
    {
		int expectedPixelColor = 0;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

        drawService.DrawPixel(2, 2, 144);
		int actualPixelColor = drawService.GetPixel(1, 1);

		EXPECT_EQ(actualPixelColor, expectedPixelColor);
    }

    TEST(DrawServiceTests, GetPixel_OutOfBounds_ReturnsDefaultValue)
    {
		int expectedPixelColor = -1;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		int actualPixelColor = drawService.GetPixel(-1, -1);

		EXPECT_EQ(actualPixelColor, expectedPixelColor);
    }

    TEST(DrawServiceTests, GetPixel_CornerCase_ReturnsCorrectValue)
    {
		int expectedPixelColor = 200;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.DrawPixel(4, 4, expectedPixelColor);
		int actualPixelColor = drawService.GetPixel(4, 4);

		EXPECT_EQ(actualPixelColor, expectedPixelColor);
    }

    TEST(DrawServiceTests, GetCanvasSize_ReturnsCorrectWidthAndHeight)
    {
		int expectedWidth = 5;
		int expectedHeight = 5;
		PixelPad::Core::Canvas canvas{ expectedWidth, expectedHeight, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		auto [width, height] = drawService.GetCanvasSize();

		EXPECT_EQ(width, expectedWidth);
		EXPECT_EQ(height, expectedHeight);
    }

    TEST(DrawServiceTests, GetCanvasSize_AfterResize_ReturnsNewSize)
    {
		int expectedAdjustedWidth = 10;
		int expectedAdjustedHeight = 10;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.ResizeCanvas(expectedAdjustedWidth, expectedAdjustedHeight);
		auto [width, height] = drawService.GetCanvasSize();

		EXPECT_EQ(width, expectedAdjustedWidth);
		EXPECT_EQ(height, expectedAdjustedHeight);
    }

    TEST(DrawServiceTests, GetCanvasSize_OnEmptyCanvas_ReturnsZeros)
    {
		int expectedWidth = 0;
		int expectedHeight = 0;
		PixelPad::Core::Canvas canvas{ expectedWidth, expectedHeight, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		auto [width, height] = drawService.GetCanvasSize();

		EXPECT_EQ(width, expectedWidth);
		EXPECT_EQ(height, expectedHeight);
    }

    TEST(DrawServiceTests, DrawLine_StraightHorizontalLine_DrawsCorrectly)
    {
        int expectedColor = 170;
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.DrawLine(0, 5, 0, 5, expectedColor);

		EXPECT_EQ(canvas.GetPixel(0, 5), expectedColor);
    }

    TEST(DrawServiceTests, DrawLine_StraightVerticalLine_DrawsCorrectly)
    {
        int expectedColor = 170;
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.DrawLine(5, 0, 5, 0, expectedColor);

		EXPECT_EQ(canvas.GetPixel(5, 0), expectedColor);
    }

    TEST(DrawServiceTests, DrawLine_DiagonalLine_DrawsCorrectly)
    {
        int expectedColor = 170;
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.DrawLine(0, 0, 5, 5, expectedColor);

		EXPECT_EQ(canvas.GetPixel(5, 5), expectedColor);
    }

    TEST(DrawServiceTests, DrawLine_NegativeDirection_DrawsCorrectly)
    {
		int expectedColor = 160;
		PixelPad::Core::Canvas canvas{ 12, 12, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.DrawLine(8, 8, 0, 0, expectedColor);

		EXPECT_EQ(canvas.GetPixel(0, 0), expectedColor);
    }

    TEST(DrawServiceTests, DrawLine_SinglePixel_DrawsCorrectly)
    {
		int expectedColor = 150;
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.DrawLine(5, 5, 5, 5, expectedColor);

		EXPECT_EQ(canvas.GetPixel(5, 5), expectedColor);
    }

    TEST(DrawServiceTests, DrawLine_OutOfBounds_DoesNotThrow)
    {
		int expectedColor = 150;
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		EXPECT_NO_THROW(drawService.DrawLine(-1, -1, 15, 15, expectedColor));
    }

    TEST(DrawServiceTests, DrawLine_OverlappingExistingPixels_OverwritesColor)
    {
		int expectedColor = 200;
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.DrawPixel(5, 5, 100);
		drawService.DrawLine(5, 5, 5, 5, expectedColor);

		EXPECT_EQ(canvas.GetPixel(5, 5), expectedColor);
    }

    TEST(DrawServiceTests, DrawLine_ZeroLengthLine_DoesNotAlterCanvas)
    {
		int expectedColor = 20;
		PixelPad::Core::Canvas canvas{ 10, 10, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.DrawPixel(5, 5, expectedColor);
		drawService.DrawLine(0, 0, 0, 0, 120);

		EXPECT_EQ(canvas.GetPixel(5, 5), expectedColor);
    }

    TEST(DrawServiceTests, DrawLine_LongLineBeyondCanvas_OnlyDrawsWithinBounds)
    {
		int expectedColor = 100;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.DrawLine(0, 0, 100, 100, expectedColor);

		EXPECT_EQ(canvas.GetPixel(1, 1), expectedColor);
		EXPECT_EQ(canvas.GetPixel(2, 2), expectedColor);
		EXPECT_EQ(canvas.GetPixel(3, 3), expectedColor);
		EXPECT_EQ(canvas.GetPixel(4, 4), expectedColor);
		EXPECT_EQ(canvas.GetPixel(5, 5), -1);
		EXPECT_EQ(canvas.GetPixel(6, 6), -1);
    }

    TEST(DrawServiceTests, DrawLine_SmallCanvasLine_DoesNotOverflow)
    {
		int expectedColor = 100;
		PixelPad::Core::Canvas canvas{ 2, 2, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.DrawLine(0, 0, 1, 1, expectedColor);

		EXPECT_EQ(canvas.GetPixel(0, 0), expectedColor);
    }

    TEST(DrawServiceTests, DrawLine_LargeCanvasLine_DrawsCorrectly)
    {
		int expectedColor = 100;
		PixelPad::Core::Canvas canvas{ 100, 100, 0 };
		PixelPad::Application::DrawService drawService{ canvas };

		drawService.DrawLine(0, 0, 99, 99, expectedColor);

		EXPECT_EQ(canvas.GetPixel(50, 50), expectedColor);
    }

    TEST(DrawServiceTests, DrawLine_CollinearOverlappingLines_OnlyOneLineDrawn)
    {
        int expectedColor = 120;
        PixelPad::Core::Canvas canvas{ 10, 10, 0 }; 
        PixelPad::Application::DrawService drawService{ canvas };

        drawService.DrawLine(0, 0, 5, 9, expectedColor);

        drawService.DrawLine(2, 0, 7, 9, expectedColor);

        for (int i = 0; i <= 5; ++i)
        {
            int x = i;
            int y = (i * 9) / 5;  // Adjusted line equation to match endY = 9
            if (x >= 0 && x < 10 && y >= 0 && y < 10)  // Ensure within bounds
            {
                EXPECT_EQ(canvas.GetPixel(x, y), expectedColor);
            }
        }

        for (int i = 2; i <= 7; ++i)
        {
            int x = i;
            int y = (i * 9) / 5;  // Adjusted line equation to match endY = 9
            if (x >= 0 && x < 10 && y >= 0 && y < 10)  // Ensure within bounds
            {
                EXPECT_EQ(canvas.GetPixel(x, y), expectedColor);
            }
        }
    }

    TEST(DrawServiceTests, SaveCanvasState_ShouldSaveCanvasState_WhenCalled)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::DrawService drawService{ canvas };
        drawService.DrawPixel(2, 2, 123);

        drawService.SaveCanvasState();

        EXPECT_EQ(canvas.GetPixel(2, 2), 123);
    }

    TEST(DrawServiceTests, LoadCanvasState_ShouldRestoreCanvasState_WhenCalled)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::DrawService drawService{ canvas };
        drawService.DrawPixel(2, 2, 123);
        drawService.SaveCanvasState();

        drawService.DrawPixel(2, 2, 255);
        drawService.LoadCanvasState();

        EXPECT_EQ(canvas.GetPixel(2, 2), 123);
    }

    TEST(DrawServiceTests, LoadCanvasState_ShouldDoNothing_WhenNoSnapshotHasBeenSaved)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::DrawService drawService{ canvas };

        drawService.LoadCanvasState();

        EXPECT_EQ(canvas.GetPixel(2, 2), 0);
    }
}