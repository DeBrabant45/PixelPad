#include <gtest/gtest.h>
#include "Graphics/Canvas.hpp"
#include "Tools/FillTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Tests::Core
{
	// Moving code to here from Application service
	//TEST(DrawServiceTests, FillCanvas_SetsAllPixelsToColor)
	//{
	//	int expectedPixelColor = 100;
	//	PixelPad::Core::Canvas canvas{ 5, 5, 0 };
	//	PixelPad::Application::DrawService drawService{ canvas };

	//	drawService.FillCanvas(expectedPixelColor);

	//	EXPECT_EQ(canvas.GetPixel(1, 1), expectedPixelColor);
	//}

	//TEST(DrawServiceTests, FillCanvas_WithNegativeColor_SetsAllPixel)
	//{
	//	int expectedPixelColor = -155;
	//	PixelPad::Core::Canvas canvas{ 5, 5, 0 };
	//	PixelPad::Application::DrawService drawService{ canvas };

	//	drawService.FillCanvas(expectedPixelColor);

	//	EXPECT_EQ(canvas.GetPixel(1, 1), expectedPixelColor);
	//}

	//TEST(DrawServiceTests, FillCanvas_WithZero_SetsAllPixelsToZero)
	//{
	//	int expectedPixelColor = 0;
	//	PixelPad::Core::Canvas canvas{ 5, 5, 0 };
	//	PixelPad::Application::DrawService drawService{ canvas };

	//	drawService.FillCanvas(expectedPixelColor);

	//	EXPECT_EQ(canvas.GetPixel(1, 1), expectedPixelColor);
	//}

	//TEST(DrawServiceTests, FillCanvas_AfterDrawingPixels_OverridesAllPixels)
	//{
	//	int expectedFillColor = 200;
	//	PixelPad::Core::Canvas canvas{ 5, 5, 0 };
	//	PixelPad::Application::DrawService drawService{ canvas };

	//	drawService.DrawPixel(1, 1, 100);
	//	drawService.DrawPixel(2, 2, 150);
	//	drawService.FillCanvas(expectedFillColor);

	//	EXPECT_EQ(canvas.GetPixel(1, 1), expectedFillColor);
	//	EXPECT_EQ(canvas.GetPixel(2, 2), expectedFillColor);
	//}

	//TEST(DrawServiceTests, FillCanvas_WithZeroCanvas_DoesNotThrow)
	//{
	//	int fillColor = 215;
	//	PixelPad::Core::Canvas canvas{ 0, 0, 0 };
	//	PixelPad::Application::DrawService drawService{ canvas };

	//	EXPECT_NO_THROW(drawService.FillCanvas(fillColor));
	//	EXPECT_EQ(canvas.GetPixel(0, 0), -1);
	//}
}