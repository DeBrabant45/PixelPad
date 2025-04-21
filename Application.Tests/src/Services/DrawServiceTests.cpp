#include <gtest/gtest.h>
#include "Services/DrawService.hpp"
#include "CanvasModel.hpp"

namespace ApplicationTests 
{
    TEST(DrawServiceTests, Constructor_DoesNotThrowAndCanvasIsCorrectSize)
    {
        Core::CanvasModel canvasModel{ 8, 6 };
        Application::DrawService drawService{ canvasModel };

        EXPECT_EQ(canvasModel.GetWidth(), 8);
        EXPECT_EQ(canvasModel.GetHeight(), 6);
    }

    TEST(DrawServiceTests, DrawPixel_SetsCorrectPixelColor)
    {
        int x = 2;
        int y = 3;
        int expectedPixelColor = 42;
        Core::CanvasModel canvasModel{ 5, 5 };
        Application::DrawService drawService{ canvasModel };

        drawService.DrawPixel(x, y, expectedPixelColor);

        EXPECT_EQ(canvasModel.GetPixel(x, y), expectedPixelColor);
    }

    TEST(DrawServiceTests, DrawPixel_OutOfBounds_DoesNotThrow)
    {
        Core::CanvasModel canvasModel{ 5, 5 };
        Application::DrawService drawService{ canvasModel };

        EXPECT_NO_THROW(drawService.DrawPixel(-1, -1, 123));
        EXPECT_NO_THROW(drawService.DrawPixel(10, 10, 255));
    }

    TEST(DrawServiceTests, DrawPixel_MultipleCalls_UpdateMultiplePixels)
    {
        Core::CanvasModel canvasModel{ 6, 6 };
        Application::DrawService drawService{ canvasModel };

        drawService.DrawPixel(5, 5, 200);
        drawService.DrawPixel(2, 2, 190);
        drawService.DrawPixel(3, 3, 180);

        EXPECT_EQ(canvasModel.GetPixel(5, 5), 200);
        EXPECT_EQ(canvasModel.GetPixel(2, 2), 190);
        EXPECT_EQ(canvasModel.GetPixel(3, 3), 180);
    }

    TEST(DrawServiceTests, DrawPixel_NegativeCoordinates_DoesNotThrow)
    {
        Core::CanvasModel canvasModel{ 6, 6 };
        Application::DrawService drawService{ canvasModel };

        EXPECT_NO_THROW(drawService.DrawPixel(-1, -1, 240));
    }

    TEST(DrawServiceTests, DrawPixel_ColorOverwrite_UpdatesPixelColor)
    {
        Core::CanvasModel canvasModel{ 6, 6 };
        Application::DrawService drawService{ canvasModel };

        drawService.DrawPixel(1, 1, 255);
        drawService.DrawPixel(1, 1, 100);

        EXPECT_EQ(canvasModel.GetPixel(1, 1), 100);
    }

    TEST(DrawServiceTests, DrawPixel_MinEdgeCoordinates_SetsPixelColor)
    {
        Core::CanvasModel canvasModel{ 1, 1 };
        Application::DrawService drawService{ canvasModel };

        drawService.DrawPixel(0, 0, 200);

        EXPECT_EQ(canvasModel.GetPixel(0, 0), 200);
    }

    TEST(DrawServiceTests, DrawPixel_MaxEdgeCoordinates_SetsPixelColor)
    {
        Core::CanvasModel canvasModel{ 5, 5 };
        Application::DrawService drawService{ canvasModel };

        drawService.DrawPixel(4, 4, 155);

        EXPECT_EQ(canvasModel.GetPixel(4, 4), 155);
    }

    TEST(DrawServiceTests, ResizeCanvas_ChangesCanvasSizeCorrectly)
    {
        int expectedWidth = 10;
        int expectedHeight = 10;
        Core::CanvasModel canvasModel{ 5, 5 };
        Application::DrawService drawService{ canvasModel };

        drawService.ResizeCanvas(expectedWidth, expectedHeight);

        EXPECT_EQ(canvasModel.GetWidth(), expectedWidth);
        EXPECT_EQ(canvasModel.GetHeight(), expectedHeight);
    }

    TEST(DrawServiceTests, ResizeCanvas_ShrinksCanvas_ClearsOrPreservesData)
    {
        Core::CanvasModel canvasModel{ 10, 10 };
        Application::DrawService drawService{ canvasModel };

        drawService.ResizeCanvas(5, 5);
        
        EXPECT_EQ(canvasModel.GetPixel(10, 10), -1);
    }

    TEST(DrawServiceTests, ResizeCanvas_ExpandsCanvas_SetsNewPixelsToDefault)
    {
        int expectedWidth = 5;
        int expectedHeight = 5;
        int expectedPixelColor = 0;
        Core::CanvasModel canvasModel{ expectedWidth, expectedHeight };
        Application::DrawService drawService{ canvasModel };

        canvasModel.Fill(155);
        drawService.ResizeCanvas(7, 7);

        EXPECT_EQ(canvasModel.GetPixel(expectedWidth, expectedHeight), expectedPixelColor);
    }

    TEST(DrawServiceTests, ResizeCanvas_ZeroSize_HandlesGracefully)
    {
        Core::CanvasModel canvasModel{ 5, 5 };
		Application::DrawService drawService{ canvasModel };

		EXPECT_NO_THROW(drawService.ResizeCanvas(0, 0));
		EXPECT_EQ(canvasModel.GetWidth(), 0);
		EXPECT_EQ(canvasModel.GetHeight(), 0);
    }

    TEST(DrawServiceTests, ResizeCanvas_NegativeValues_DoesNotThrow)
    {
		Core::CanvasModel canvasModel{ 5, 5 };
		Application::DrawService drawService{ canvasModel };

		EXPECT_NO_THROW(drawService.ResizeCanvas(-5, -5));
    }

    TEST(DrawServiceTests, FillCanvas_SetsAllPixelsToColor)
    {
		int expectedPixelColor = 100;
		Core::CanvasModel canvasModel{ 5, 5 };
		Application::DrawService drawService{ canvasModel };

		drawService.FillCanvas(expectedPixelColor);

		EXPECT_EQ(canvasModel.GetPixel(1, 1), expectedPixelColor);
    }

    TEST(DrawServiceTests, FillCanvas_WithNegativeColor_SetsAllPixel)
    {
		int expectedPixelColor = -155;
		Core::CanvasModel canvasModel{ 5, 5 };
		Application::DrawService drawService{ canvasModel };

		drawService.FillCanvas(expectedPixelColor);

		EXPECT_EQ(canvasModel.GetPixel(1, 1), expectedPixelColor);
    }

    TEST(DrawServiceTests, FillCanvas_WithZero_SetsAllPixelsToZero)
    {
		int expectedPixelColor = 0;
		Core::CanvasModel canvasModel{ 5, 5 };
		Application::DrawService drawService{ canvasModel };

		drawService.FillCanvas(expectedPixelColor);

		EXPECT_EQ(canvasModel.GetPixel(1, 1), expectedPixelColor);
    }

    TEST(DrawServiceTests, FillCanvas_AfterDrawingPixels_OverridesAllPixels)
    {
		int expectedFillColor = 200;
		Core::CanvasModel canvasModel{ 5, 5 };
		Application::DrawService drawService{ canvasModel };

		drawService.DrawPixel(1, 1, 100);
		drawService.DrawPixel(2, 2, 150);
		drawService.FillCanvas(expectedFillColor);

		EXPECT_EQ(canvasModel.GetPixel(1, 1), expectedFillColor);
		EXPECT_EQ(canvasModel.GetPixel(2, 2), expectedFillColor);
    }

    TEST(DrawServiceTests, FillCanvas_WithZeroCanvas_DoesNotThrow)
    {
		int fillColor = 215;
		Core::CanvasModel canvasModel{ 0, 0 };
		Application::DrawService drawService{ canvasModel };

		EXPECT_NO_THROW(drawService.FillCanvas(fillColor));
		EXPECT_EQ(canvasModel.GetPixel(0, 0), -1);
    }

    TEST(DrawServiceTests, ClearCanvas_ResetsAllPixelsToDefault)
    {
		int expectedPixelColor = 0;
		Core::CanvasModel canvasModel{ 5, 5 };
		Application::DrawService drawService{ canvasModel };

		canvasModel.Fill(100);
		drawService.ClearCanvas();

		EXPECT_EQ(canvasModel.GetPixel(1, 1), expectedPixelColor);
		EXPECT_EQ(canvasModel.GetPixel(2, 2), expectedPixelColor);
		EXPECT_EQ(canvasModel.GetPixel(3, 3), expectedPixelColor);
		EXPECT_EQ(canvasModel.GetPixel(4, 4), expectedPixelColor);
    }

    TEST(DrawServiceTests, ClearCanvas_EmptyCanvas_DoesNotThrow)
    {
		Core::CanvasModel canvasModel{ 0, 0 };
		Application::DrawService drawService{ canvasModel };

		EXPECT_NO_THROW(drawService.ClearCanvas());
    }

    TEST(DrawServiceTests, ClearCanvas_AfterResize_StillClearsAllPixels)
    {
        int expectedPixelColor = 0;
		Core::CanvasModel canvasModel{ 5, 5 };
		Application::DrawService drawService{ canvasModel };

        drawService.ResizeCanvas(3, 3);
		drawService.ClearCanvas();

		EXPECT_EQ(canvasModel.GetPixel(1, 1), expectedPixelColor);
		EXPECT_EQ(canvasModel.GetPixel(2, 2), expectedPixelColor);
    }

    TEST(DrawServiceTests, GetPixel_ReturnsCorrectValue_WhenPixelIsSet)
    {
		int expectedPixelColor = 123;
		Core::CanvasModel canvasModel{ 5, 5 };
		Application::DrawService drawService{ canvasModel };

		drawService.DrawPixel(2, 2, expectedPixelColor);
		int actualPixelColor = drawService.GetPixel(2, 2);

		EXPECT_EQ(actualPixelColor, expectedPixelColor);
    }

    TEST(DrawServiceTests, GetPixel_DefaultValue_WhenPixelWasNotModified)
    {
		int expectedPixelColor = 0;
		Core::CanvasModel canvasModel{ 5, 5 };
		Application::DrawService drawService{ canvasModel };

        drawService.DrawPixel(2, 2, 144);
		int actualPixelColor = drawService.GetPixel(1, 1);

		EXPECT_EQ(actualPixelColor, expectedPixelColor);
    }

    TEST(DrawServiceTests, GetPixel_OutOfBounds_ReturnsDefaultValue)
    {
		int expectedPixelColor = -1;
		Core::CanvasModel canvasModel{ 5, 5 };
		Application::DrawService drawService{ canvasModel };

		int actualPixelColor = drawService.GetPixel(-1, -1);

		EXPECT_EQ(actualPixelColor, expectedPixelColor);
    }

    TEST(DrawServiceTests, GetPixel_CornerCase_ReturnsCorrectValue)
    {
		int expectedPixelColor = 200;
		Core::CanvasModel canvasModel{ 5, 5 };
		Application::DrawService drawService{ canvasModel };

		drawService.DrawPixel(4, 4, expectedPixelColor);
		int actualPixelColor = drawService.GetPixel(4, 4);

		EXPECT_EQ(actualPixelColor, expectedPixelColor);
    }
}