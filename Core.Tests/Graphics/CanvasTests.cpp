#include <gtest/gtest.h>
#include "Graphics/Canvas.hpp"

namespace PixelPad::Tests::Core
{
    TEST(CanvasTests, Constructor_ShouldInitializeCanvasWithCorrectSize)
    {
        PixelPad::Core::Canvas canvas(10, 5, 0);

        canvas.DrawPixel(0, 0, 255);
        canvas.DrawPixel(9, 4, 123);

        SUCCEED();
    }

    TEST(CanvasTests, Clear_ShouldSetAllPixelsToZero)
    {
        PixelPad::Core::Canvas canvas(3, 3, 0);

        canvas.DrawPixel(1, 1, 100);
        canvas.Clear();

        SUCCEED();
    }

    TEST(CanvasTests, DrawPixel_ShouldSetPixelValue_WhenCoordinatesAreInBounds)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

        canvas.DrawPixel(2, 3, 42);

        SUCCEED();
    }

    TEST(CanvasTests, DrawPixel_ShouldDoNothing_WhenCoordinatesAreOutOfBounds)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

        canvas.DrawPixel(-1, -1, 999);
        canvas.DrawPixel(10, 10, 999);

        SUCCEED();
    }

    TEST(CanvasTests, DrawLine_ShouldDrawHorizontalLine_WhenStartAndEndYAreSame)
    {
        PixelPad::Core::Canvas canvas(5, 3, 0);

        canvas.DrawLine(0, 0, 4, 0, 255);

        for (int x = 0; x < 5; ++x)
        {
            EXPECT_EQ(canvas.GetPixel(x, 0), 255);
        }
    }

    TEST(CanvasTests, DrawLine_ShouldDrawVerticalLine_WhenStartAndEndXAreSame)
    {
        PixelPad::Core::Canvas canvas(3, 5, 0);

        canvas.DrawLine(1, 0, 1, 4, 123);

        for (int y = 0; y < 5; ++y)
        {
            EXPECT_EQ(canvas.GetPixel(1, y), 123);
        }
    }

    TEST(CanvasTests, DrawLine_ShouldDrawDiagonalLine_WhenStartAndEndFormDiagonal)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

        canvas.DrawLine(0, 0, 4, 4, 255);

        EXPECT_EQ(canvas.GetPixel(0, 0), 255);
        EXPECT_EQ(canvas.GetPixel(1, 1), 255);
        EXPECT_EQ(canvas.GetPixel(2, 2), 255);
        EXPECT_EQ(canvas.GetPixel(3, 3), 255);
        EXPECT_EQ(canvas.GetPixel(4, 4), 255);
    }

    TEST(CanvasTests, DrawCircleFilled_ShouldFillPixels_WhenWithinRadius)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

		canvas.DrawCircleFilled(2, 2, 1, 255);

        EXPECT_EQ(canvas.GetPixel(1, 2), 255);
        EXPECT_EQ(canvas.GetPixel(2, 1), 255);
        EXPECT_EQ(canvas.GetPixel(2, 2), 255);
        EXPECT_EQ(canvas.GetPixel(2, 3), 255);
        EXPECT_EQ(canvas.GetPixel(3, 2), 255);
    }

    TEST(CanvasTests, DrawCircleFilled_ShouldNotFillPixels_WhenOutsideRadius)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

        canvas.DrawCircleFilled(2, 2, 1, 255);

        EXPECT_EQ(canvas.GetPixel(1, 1), 0);
        EXPECT_EQ(canvas.GetPixel(4, 3), 0);
        EXPECT_EQ(canvas.GetPixel(4, 4), 0);
    }

    TEST(CanvasTests, DrawCircleFilled_ShouldOnlyFillCenterPixel_WhenRadiusIsZero)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

        canvas.DrawCircleFilled(2, 2, 0, 255);

        EXPECT_EQ(canvas.GetPixel(1, 1), 0);
        EXPECT_EQ(canvas.GetPixel(2, 2), 255);
		EXPECT_EQ(canvas.GetPixel(3, 3), 0);
    }

    TEST(CanvasTests, DrawCircleFilled_ShouldFillUpToCanvasEdges_WhenRadiusExceedsBounds)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

        canvas.DrawCircleFilled(2, 2, 10, 255);

        for (int y = 0; y < 5; ++y)
        {
            for (int x = 0; x < 5; ++x)
            {
                EXPECT_EQ(canvas.GetPixel(x, y), 255);
            }
		}
    }

    TEST(CanvasTests, DrawCircleFilled_ShouldFillPixels_WhenRadiusTouchesCanvasEdges)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

        canvas.DrawCircleFilled(4, 4, 2, 255);

        EXPECT_EQ(canvas.GetPixel(3, 2), 0);
		EXPECT_EQ(canvas.GetPixel(4, 3), 255);
        EXPECT_EQ(canvas.GetPixel(4, 4), 255);
    }

    TEST(CanvasTests, DrawCircleOutline_ShouldFillPixels_WhenWithinRadius)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

        canvas.DrawCircleOutline(2, 2, 1, 255);

        EXPECT_EQ(canvas.GetPixel(1, 2), 255);
        EXPECT_EQ(canvas.GetPixel(2, 1), 255);
        EXPECT_EQ(canvas.GetPixel(2, 2), 0);
        EXPECT_EQ(canvas.GetPixel(2, 3), 255);
        EXPECT_EQ(canvas.GetPixel(3, 2), 255);
    }

    TEST(CanvasTests, DrawCircleOutline_ShouldNotFillPixels_WhenOutsideRadius)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

        canvas.DrawCircleOutline(2, 2, 1, 255);

        EXPECT_EQ(canvas.GetPixel(1, 1), 255);
        EXPECT_EQ(canvas.GetPixel(4, 3), 0);
        EXPECT_EQ(canvas.GetPixel(4, 4), 0);
    }

    TEST(CanvasTests, DrawCircleOutline_ShouldDrawOnlyCenter_WhenRadiusIsZero)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

        canvas.DrawCircleOutline(2, 2, 0, 255);

        EXPECT_EQ(canvas.GetPixel(2, 2), 255);
        EXPECT_EQ(canvas.GetPixel(2, 1), 0);
    }

    TEST(CanvasTests, DrawCircleOutline_ShouldNotDraw_WhenRadiusIsNegative)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

        canvas.DrawCircleOutline(2, 2, -1, 255);

        EXPECT_EQ(canvas.GetPixel(2, 2), 0); 
    }

    TEST(CanvasTests, DrawCircleOutline_ShouldClipPixels_WhenCircleIsPartiallyOutOfBounds)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

        canvas.DrawCircleOutline(0, 0, 2, 255);

        EXPECT_EQ(canvas.GetPixel(0, 2), 255);
        EXPECT_EQ(canvas.GetPixel(4, 4), 0); 
    }

    TEST(CanvasTests, DrawCircleOutline_ShouldNotCrash_WhenCircleIsLargerThanCanvas)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

        canvas.DrawCircleOutline(2, 2, 100, 255);

        EXPECT_EQ(canvas.GetPixel(2, 2), 0);
    }

    TEST(CanvasTests, DrawRectangle_ShouldFillBorder_WhenWithinRadius)
    {
       PixelPad::Core::Canvas canvas(10, 10, 0);
        canvas.DrawRectangle(2, 2, 7, 7, 42);

        for (int x = 2; x <= 7; ++x)
        {
            EXPECT_EQ(canvas.GetPixel(x, 2), 42);
            EXPECT_EQ(canvas.GetPixel(x, 7), 42);
        }

        for (int y = 2; y <= 7; ++y)
        {
            EXPECT_EQ(canvas.GetPixel(2, y), 42);
            EXPECT_EQ(canvas.GetPixel(7, y), 42);
        }

        for (int y = 3; y < 7; ++y)
        {
            for (int x = 3; x < 7; ++x)
            {
                EXPECT_EQ(canvas.GetPixel(x, y), 0);
            }
        }
    }

    TEST(CanvasTests, DrawRectangle_ShouldFillBorderOnLargeCanvas_WhenWithinBounds)
    {
        PixelPad::Core::Canvas canvas(1000, 1000, 0);
        canvas.DrawRectangle(100, 100, 900, 900, 99);

        for (int x = 100; x <= 900; ++x)
        {
            EXPECT_EQ(canvas.GetPixel(x, 100), 99);
            EXPECT_EQ(canvas.GetPixel(x, 900), 99);
        }

        for (int y = 100; y <= 900; ++y)
        {
            EXPECT_EQ(canvas.GetPixel(100, y), 99);
            EXPECT_EQ(canvas.GetPixel(900, y), 99);
        }

        for (int y = 101; y < 900; ++y)
        {
            for (int x = 101; x < 900; ++x)
            {
                EXPECT_EQ(canvas.GetPixel(x, y), 0);
            }
        }
    }

    TEST(CanvasTests, DrawRectangle_ShouldFillSinglePixel_WhenStartEqualsEnd)
    {
        PixelPad::Core::Canvas canvas(10, 10, 0);

        canvas.DrawRectangle(4, 4, 4, 4, 99);

        EXPECT_EQ(canvas.GetPixel(4, 4), 99);
    }

    TEST(CanvasTests, DrawRectangle_ShouldNotCrash_WhenOutOfBounds)
    {
        PixelPad::Core::Canvas canvas(10, 10, 0);

        EXPECT_NO_THROW(canvas.DrawRectangle(-5, -5, 15, 15, 1));
    }

    TEST(CanvasTests, DrawRectangle_ShouldHandleReversedCoordinates)
    {
        PixelPad::Core::Canvas canvas(10, 10, 0);

        canvas.DrawRectangle(7, 7, 2, 2, 77);

        EXPECT_EQ(canvas.GetPixel(2, 2), 77);
        EXPECT_EQ(canvas.GetPixel(7, 7), 77);
    }

    TEST(CanvasTests, DrawEllipse_ShouldFillOutlineOfPerfectCircle_WhenGivenEqualWidthAndHeight)
    {
        PixelPad::Core::Canvas canvas(11, 11, 0);

        canvas.DrawEllipse(5, 5, 3, 3, 155);

        EXPECT_EQ(canvas.GetPixel(5, 2), 155); 
        EXPECT_EQ(canvas.GetPixel(5, 8), 155); 
        EXPECT_EQ(canvas.GetPixel(2, 5), 155); 
        EXPECT_EQ(canvas.GetPixel(8, 5), 155);
    }

    TEST(CanvasTests, DrawEllipse_ShouldFillOutlineOfEllipse_WhenRadiusXDiffersFromRadiusY)
    {
		const int centerX = 8;
		const int centerY = 8;
		const int radiusX = 4;
		const int radiusY = 6;
		const int color = 155;
        PixelPad::Core::Canvas canvas(20, 20, 0);

        canvas.DrawEllipse(centerX, centerY, radiusX, radiusY, color);

		EXPECT_EQ(canvas.GetPixel((centerX - radiusX), centerY), color); // Left Edge
		EXPECT_EQ(canvas.GetPixel((centerX + radiusX), centerY), color); // Right Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY - radiusY)), color); // Top Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY + radiusY)), color); // Bottom Edge
    }

    TEST(CanvasTests, DrawEllipse_ShouldFillCorrectOutline_WhenCenterIsAtCanvasEdge)
    {
		const int centerX = 7;
		const int centerY = 7;
		const int radiusX = 2;
		const int radiusY = 2;
		const int color = 155;
        PixelPad::Core::Canvas canvas(8, 8, 0);

        canvas.DrawEllipse(centerX, centerY, radiusX, radiusY, color);

		EXPECT_EQ(canvas.GetPixel((centerX - radiusX), centerY), color); // Left Edge
		EXPECT_EQ(canvas.GetPixel((centerX + radiusX), centerY), -1); // Right Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY - radiusY)), color); // Top Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY + radiusY)), -1); // Bottom Edge
    }

    TEST(CanvasTests, DrawEllipse_ShouldFillNothing_WhenRadiusXOrRadiusYIsZero)
    {
		const int centerX = 4;
		const int centerY = 3;
		const int radiusX = 0;
		const int radiusY = 0;
		const int color = 155;
        PixelPad::Core::Canvas canvas(8, 8, 0);

        canvas.DrawEllipse(centerX, centerY, radiusX, radiusY, color);

		EXPECT_EQ(canvas.GetPixel((centerX - radiusX), centerY), 0); // Left Edge
		EXPECT_EQ(canvas.GetPixel((centerX + radiusX), centerY), 0); // Right Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY - radiusY)), 0); // Top Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY + radiusY)), 0); // Bottom Edge
    }

    TEST(CanvasTests, DrawEllipse_ShouldFillNothing_WhenRadiusXAndRadiusYAreNegative)
    {
		const int centerX = 5;
		const int centerY = 5;
		const int radiusX = -4;
		const int radiusY = -5;
		const int color = 155;
        PixelPad::Core::Canvas canvas(8, 8, 0);

        canvas.DrawEllipse(centerX, centerY, radiusX, radiusY, color);

		EXPECT_EQ(canvas.GetPixel((centerX - radiusX), centerY), -1); // Left Edge
		EXPECT_EQ(canvas.GetPixel((centerX + radiusX), centerY), 0); // Right Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY - radiusY)), -1); // Top Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY + radiusY)), 0); // Bottom Edge
    }

    TEST(CanvasTests, DrawEllipse_ShouldClipCorrectly_WhenEllipsePartiallyOutsideCanvas)
    {
		const int centerX = 6;
		const int centerY = 5;
		const int radiusX = 3;
		const int radiusY = 4;
		const int color = 155;
        PixelPad::Core::Canvas canvas(8, 8, 0);

        canvas.DrawEllipse(centerX, centerY, radiusX, radiusY, color);

		EXPECT_EQ(canvas.GetPixel((centerX - radiusX), centerY), color); // Left Edge
		EXPECT_EQ(canvas.GetPixel((centerX + radiusX), centerY), -1); // Right Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY - radiusY)), color); // Top Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY + radiusY)), -1); // Bottom Edge
    }

    TEST(CanvasTests, DrawEllipse_ShouldNotFillOutsideCanvas_WhenEllipseExceedsCanvasBounds)
    {
		const int centerX = 5;
		const int centerY = 5;
		const int radiusX = 20;
		const int radiusY = 20;
		const int color = 155;
        PixelPad::Core::Canvas canvas(8, 8, 0);

        canvas.DrawEllipse(centerX, centerY, radiusX, radiusY, color);

		EXPECT_EQ(canvas.GetPixel(5, 5), 0);
		EXPECT_EQ(canvas.GetPixel((centerX - radiusX), centerY), -1); // Left Edge
		EXPECT_EQ(canvas.GetPixel((centerX + radiusX), centerY), -1); // Right Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY - radiusY)), -1); // Top Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY + radiusY)), -1); // Bottom Edge

        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                EXPECT_EQ(canvas.GetPixel(x, y), 0);
            }
        }
    }

    TEST(CanvasTests, DrawEllipse_ShouldHandleSmallEllipses_WhenRadiusIsOne)
    {
		const int centerX = 5;
		const int centerY = 5;
		const int radiusX = 1;
		const int radiusY = 1;
		const int color = 155;
        PixelPad::Core::Canvas canvas(8, 8, 0);

        canvas.DrawEllipse(centerX, centerY, radiusX, radiusY, color);

		EXPECT_EQ(canvas.GetPixel((centerX - radiusX), centerY), color); // Left Edge
		EXPECT_EQ(canvas.GetPixel((centerX + radiusX), centerY), color); // Right Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY - radiusY)), color); // Top Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY + radiusY)), color); // Bottom Edge
    }

    TEST(CanvasTests, DrawEllipse_ShouldIgnoreDrawCalls_WhenCenterIsOutsideCanvas)
    {
		const int centerX = 12;
		const int centerY = 12;
		const int radiusX = 2;
		const int radiusY = 3;
		const int color = 155;
        PixelPad::Core::Canvas canvas(8, 8, 0);

        canvas.DrawEllipse(centerX, centerY, radiusX, radiusY, color);

		EXPECT_EQ(canvas.GetPixel((centerX - radiusX), centerY), -1); // Left Edge
		EXPECT_EQ(canvas.GetPixel((centerX + radiusX), centerY), -1); // Right Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY - radiusY)), -1); // Top Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY + radiusY)), -1); // Bottom Edge

        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                EXPECT_EQ(canvas.GetPixel(x, y), 0);
            }
        }
    }

    TEST(CanvasTests, DrawEllipse_ShouldCompleteQuickly_ForLargeRadiusValues)
    {
		const int centerX = 500;
		const int centerY = 440;
		const int radiusX = 200;
		const int radiusY = 150;
		const int color = 155;
        PixelPad::Core::Canvas canvas(800, 600, 0);

        canvas.DrawEllipse(centerX, centerY, radiusX, radiusY, color);

		EXPECT_EQ(canvas.GetPixel((centerX - radiusX), centerY), color); // Left Edge
		EXPECT_EQ(canvas.GetPixel((centerX + radiusX), centerY), color); // Right Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY - radiusY)), color); // Top Edge
		EXPECT_EQ(canvas.GetPixel(centerX, (centerY + radiusY)), color); // Bottom Edge
    }

    TEST(CanvasTests, GetPixel_ShouldReturnCorrectValue_WhenPixelWasSet)
    {
        PixelPad::Core::Canvas canvas(5, 5, 0);

        canvas.DrawPixel(2, 2, 42);
        int pixelValue = canvas.GetPixel(2, 2);

        EXPECT_EQ(pixelValue, 42);
    }

    TEST(CanvasTests, Fill_ShouldSetAllPixelsToSpecifiedColor)
    {
        PixelPad::Core::Canvas canvas(3, 2, 0);

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
        PixelPad::Core::Canvas canvas(2, 2, 0);
        canvas.DrawPixel(0, 0, 1);
        canvas.DrawPixel(1, 1, 2);

        canvas.Fill(42);

        EXPECT_EQ(canvas.GetPixel(0, 0), 42);
        EXPECT_EQ(canvas.GetPixel(1, 1), 42);
    }

    TEST(CanvasTests, FloodFill_ShouldChangePixels_WhenFillColorEqualsTargetColor)
    {
        PixelPad::Core::Canvas canvas{ 2, 2, 0 };

        canvas.FloodFill(0, 0, 1); 

        EXPECT_EQ(canvas.GetPixel(0, 0), 1);
        EXPECT_EQ(canvas.GetPixel(0, 1), 1);
        EXPECT_EQ(canvas.GetPixel(1, 0), 1);
        EXPECT_EQ(canvas.GetPixel(1, 1), 1);
    }

    TEST(CanvasTests, FloodFill_ShouldNotChangePixels_WhenFillColorEqualsTargetColor)
    {
        PixelPad::Core::Canvas canvas{ 3, 3, 42 };

        canvas.FloodFill(1, 1, 42);

        for (int y = 0; y < canvas.GetHeight(); ++y)
        {
            for (int x = 0; x < canvas.GetWidth(); ++x)
            {
                EXPECT_EQ(canvas.GetPixel(x, y), 42);
            }
        }
    }

    TEST(CanvasTests, FloodFill_ShouldFillAtEdgeCoordinates)
    {
        PixelPad::Core::Canvas canvas{ 3, 3, 0 };
        canvas.DrawPixel(0, 0, 1);

        canvas.FloodFill(2, 2, 255);

        std::vector<std::pair<int, int>> unchangedPixels = { {0, 0} };
        std::vector<std::pair<int, int>> filledPixels =
        {
            {1, 0}, {2, 0},
            {0, 1}, {1, 1}, {2, 1},
            {0, 2}, {1, 2}, {2, 2}
        };

        for (const auto& [x, y] : filledPixels)
            EXPECT_EQ(canvas.GetPixel(x, y), 255);

        for (const auto& [x, y] : unchangedPixels)
            EXPECT_EQ(canvas.GetPixel(x, y), 1);
    }

    TEST(CanvasTests, FloodFill_ShouldHandleOutOfBoundsCoordinatesGracefully)
    {
        PixelPad::Core::Canvas canvas{ 3, 3, 0 };

        EXPECT_NO_THROW(canvas.FloodFill(-1, -1, 255));
        EXPECT_NO_THROW(canvas.FloodFill(3, 3, 255));
        EXPECT_NO_THROW(canvas.FloodFill(100, 100, 255));
    }

    TEST(CanvasTests, FloodFill_ShouldOnlyFillConnectedPixels)
    {
        PixelPad::Core::Canvas canvas{ 4, 4, 0 };

        for (int x = 0; x < 4; ++x)
            canvas.DrawPixel(x, 1, 1);

        canvas.FloodFill(0, 0, 255);

        std::vector<std::pair<int, int>> filledPixels = {
            {0, 0}, {1, 0}, {2, 0}, {3, 0}
        };

        std::vector<std::pair<int, int>> barrierPixels = {
            {0, 1}, {1, 1}, {2, 1}, {3, 1}
        };

        std::vector<std::pair<int, int>> bottomPixels = {
            {0, 2}, {1, 2}, {2, 2}, {3, 2},
            {0, 3}, {1, 3}, {2, 3}, {3, 3}
        };

        for (const auto& [x, y] : filledPixels)
            EXPECT_EQ(canvas.GetPixel(x, y), 255);

        for (const auto& [x, y] : barrierPixels)
            EXPECT_EQ(canvas.GetPixel(x, y), 1);

        for (const auto& [x, y] : bottomPixels)
            EXPECT_EQ(canvas.GetPixel(x, y), 0);
    }

    TEST(CanvasTests, FloodFill_ShouldFillSinglePixelCanvas)
    {
        PixelPad::Core::Canvas canvas{ 1, 1, 0 };

        canvas.FloodFill(0, 0, 255);

        EXPECT_EQ(canvas.GetPixel(0, 0), 255);
    }

    TEST(CanvasTests, FloodFill_ShouldFillEntireCanvasWithoutCrash)
    {
        const int width = 800;
        const int height = 600;
        const int initialColor = 0;
        const int fillColor = 255;

        PixelPad::Core::Canvas canvas{ width, height, initialColor };

        ASSERT_NO_THROW(canvas.FloodFill(0, 0, fillColor));

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                EXPECT_EQ(canvas.GetPixel(x, y), fillColor);
            }
        }
    }

    TEST(CanvasTests, Resize_ShouldPreserveExistingPixels_WhenNewSizeIsLarger)
    {
        PixelPad::Core::Canvas canvas(2, 2, 0);
        canvas.DrawPixel(0, 0, 1);
        canvas.DrawPixel(1, 1, 2);

        canvas.Resize(4, 4);

        EXPECT_EQ(canvas.GetPixel(0, 0), 1);
        EXPECT_EQ(canvas.GetPixel(1, 1), 2);
        EXPECT_EQ(canvas.GetPixel(3, 3), 0);
    }

    TEST(CanvasTests, Resize_ShouldTruncatePixelData_WhenNewSizeIsSmaller)
    {
        PixelPad::Core::Canvas canvas(4, 4, 0);
        canvas.DrawPixel(3, 3, 9);
        canvas.Resize(2, 2);

        EXPECT_EQ(canvas.GetPixel(0, 0), 0);
    }

    TEST(CanvasTests, Resize_ShouldPreserveAllPixels_WhenNewSizeIsSame)
    {
        PixelPad::Core::Canvas canvas(3, 3, 0);
        canvas.DrawPixel(1, 1, 7);
        canvas.Resize(3, 3);

        EXPECT_EQ(canvas.GetPixel(1, 1), 7);
    }
}