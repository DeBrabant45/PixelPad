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

    TEST(DrawServiceTests, SaveCanvasState_ShouldSaveCanvasState_WhenCalled)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::DrawService drawService{ canvas };
        canvas.DrawPixel(2, 2, 123);

        drawService.SaveCanvasState();

        EXPECT_EQ(canvas.GetPixel(2, 2), 123);
    }

    TEST(DrawServiceTests, LoadCanvasState_ShouldRestoreCanvasState_WhenCalled)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::DrawService drawService{ canvas };
        canvas.DrawPixel(2, 2, 123);
        drawService.SaveCanvasState();

        canvas.DrawPixel(2, 2, 255);
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