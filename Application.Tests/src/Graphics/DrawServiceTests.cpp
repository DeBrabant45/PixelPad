#include <gtest/gtest.h>
#include "Graphics/DrawService.hpp"
#include "Graphics/canvas.hpp"
#include "Graphics/CanvasViewport.hpp"
#include "Tools/Toolbox.hpp"
#include "Enums/MouseButton.hpp"
#include "Events/MouseButtonEvent.hpp"

namespace PixelPad::Tests::Application
{
    TEST(DrawServiceTests, Constructor_DoesNotThrowAndCanvasIsCorrectSize)
    {
        PixelPad::Core::Canvas canvas{8, 6, 0};
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };

        EXPECT_EQ(canvas.GetWidth(), 8);
        EXPECT_EQ(canvas.GetHeight(), 6);
    }

    TEST(DrawServiceTests, ResizeCanvas_ChangesCanvasSizeCorrectly)
    {
        int expectedWidth = 10;
        int expectedHeight = 10;
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };

        drawService.ResizeCanvas(expectedWidth, expectedHeight);

        EXPECT_EQ(canvas.GetWidth(), expectedWidth);
        EXPECT_EQ(canvas.GetHeight(), expectedHeight);
    }

    TEST(DrawServiceTests, ResizeCanvas_ShrinksCanvas_ClearsOrPreservesData)
    {
        PixelPad::Core::Canvas canvas{ 10, 10, 0 };
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };

        drawService.ResizeCanvas(5, 5);
        
        EXPECT_EQ(canvas.GetPixel(10, 10), -1);
    }

    TEST(DrawServiceTests, ResizeCanvas_ExpandsCanvas_SetsNewPixelsToDefault)
    {
        int expectedWidth = 5;
        int expectedHeight = 5;
        int expectedPixelColor = 0;
        PixelPad::Core::Canvas canvas{ expectedWidth, expectedHeight, 0 };
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };

        canvas.Fill(155);
        drawService.ResizeCanvas(7, 7);

        EXPECT_EQ(canvas.GetPixel(expectedWidth, expectedHeight), expectedPixelColor);
    }

    TEST(DrawServiceTests, ResizeCanvas_ZeroSize_HandlesGracefully)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };

		EXPECT_NO_THROW(drawService.ResizeCanvas(0, 0));
		EXPECT_EQ(canvas.GetWidth(), 0);
		EXPECT_EQ(canvas.GetHeight(), 0);
    }

    TEST(DrawServiceTests, ResizeCanvas_NegativeValues_DoesNotThrow)
    {
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };

		EXPECT_NO_THROW(drawService.ResizeCanvas(-5, -5));
    }

    TEST(DrawServiceTests, ClearCanvas_ResetsAllPixelsToDefault)
    {
		int expectedPixelColor = 0;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };

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
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };

		EXPECT_NO_THROW(drawService.ClearCanvas());
    }

    TEST(DrawServiceTests, ClearCanvas_AfterResize_StillClearsAllPixels)
    {
        int expectedPixelColor = 0;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };

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
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };

		auto [width, height] = drawService.GetCanvasSize();

		EXPECT_EQ(width, expectedWidth);
		EXPECT_EQ(height, expectedHeight);
    }

    TEST(DrawServiceTests, GetCanvasSize_AfterResize_ReturnsNewSize)
    {
		int expectedAdjustedWidth = 10;
		int expectedAdjustedHeight = 10;
		PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };

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
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };

		auto [width, height] = drawService.GetCanvasSize();

		EXPECT_EQ(width, expectedWidth);
		EXPECT_EQ(height, expectedHeight);
    }

    TEST(DrawServiceTests, SaveCanvasState_ShouldSaveCanvasState_WhenCalled)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };
        canvas.DrawPixel(2, 2, 123);

        drawService.SaveCanvasState();

        EXPECT_EQ(canvas.GetPixel(2, 2), 123);
    }

    TEST(DrawServiceTests, LoadCanvasState_ShouldRestoreCanvasState_WhenCalled)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };
        canvas.DrawPixel(2, 2, 123);
        drawService.SaveCanvasState();

        canvas.DrawPixel(2, 2, 255);
        drawService.LoadCanvasState();

        EXPECT_EQ(canvas.GetPixel(2, 2), 123);
    }

    TEST(DrawServiceTests, LoadCanvasState_ShouldDoNothing_WhenNoSnapshotHasBeenSaved)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };

        drawService.LoadCanvasState();

        EXPECT_EQ(canvas.GetPixel(2, 2), 0);
    }

    TEST(DrawServiceTests, ProcessDrawInput_ShouldDrawCorrectColorWithSelectedTool_WhenCalled)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Core::Color color(0, 255, 0, 255);
        PixelPad::Application::Toolbox toolbox{ canvas };
        PixelPad::Application::CanvasViewport viewport{ 5, 5, 0, 0 };
        PixelPad::Application::DrawService drawService{ canvas, toolbox };
        PixelPad::Application::MouseButtonEvent mouseEvent(2, 2, true, PixelPad::Application::MouseButton::Left);

        drawService.SetColor(color);
        drawService.SetTool(PixelPad::Core::ToolType::Pencil);
        drawService.ProcessDrawInput(mouseEvent, viewport);

        EXPECT_EQ(canvas.GetPixel(mouseEvent.X, mouseEvent.Y), color.ToRGBA());
    }
}