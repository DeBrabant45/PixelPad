#include <gtest/gtest.h>
#include "Graphics/Canvas.hpp"
#include "Tools/EllipseTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Tests::Core
{
    TEST(EllipseToolTests, Draw_ShouldFillOutlineOfPerfectCircle_WhenPressedAndReleased)
    {
        const int expectedColor = 155;
        PixelPad::Core::Canvas canvas(11, 11, 0);
		PixelPad::Core::EllipseTool ellipseTool(canvas);

		ellipseTool.Draw({ 2, 2, expectedColor, true });
		ellipseTool.Draw({ 8, 8, expectedColor, false });

        EXPECT_EQ(canvas.GetPixel(5, 2), 155);
        EXPECT_EQ(canvas.GetPixel(5, 8), 155);
        EXPECT_EQ(canvas.GetPixel(2, 5), 155);
        EXPECT_EQ(canvas.GetPixel(8, 5), 155);
    }

    TEST(EllipseToolTests, Draw_ShouldNotFill_WhenPressedOnly)
    {
        const int expectedColor = 0;
        PixelPad::Core::Canvas canvas(10, 10, expectedColor);
        PixelPad::Core::EllipseTool ellipseTool(canvas);

        ellipseTool.Draw({ 3, 4, 100, true });

        EXPECT_EQ(canvas.GetPixel(3, 4), expectedColor);
    }

    TEST(EllipseToolTests, Draw_ShouldReset_WhenRepeatedPressedAndReleased)
    {
        const int expectedFistColor = 100;
        const int expectedSecondColor = 200;
        PixelPad::Core::Canvas canvas(10, 10, 0);
        PixelPad::Core::EllipseTool ellipseTool(canvas);

        ellipseTool.Draw({ 2, 2, expectedFistColor, true });
        ellipseTool.Draw({ 6, 6, expectedFistColor, false });

        ellipseTool.Draw({ 1, 1, expectedSecondColor, true });
        ellipseTool.Draw({ 3, 3, expectedSecondColor, false });

        EXPECT_EQ(canvas.GetPixel(2, 1), expectedSecondColor);
        EXPECT_EQ(canvas.GetPixel(3, 2), expectedSecondColor);
        EXPECT_EQ(canvas.GetPixel(4, 2), expectedFistColor);
    }
}