#include <gtest/gtest.h>
#include "Graphics/Canvas.hpp"
#include "Tools/PencilTool.hpp"
#include "Tools/DrawCommand.hpp"

namespace PixelPad::Tests::Core
{
    TEST(PencilToolTests, Draw_ShouldSetCorrectPixelColor)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Core::PencilTool pencilTool{ canvas };
        PixelPad::Core::DrawCommand drawCommand{ 2, 3, 42, true };

        pencilTool.Draw(drawCommand);

        EXPECT_EQ(canvas.GetPixel(drawCommand.X, drawCommand.Y), drawCommand.Color);
    }

    TEST(PencilToolTests, Draw_ShouldNoThrowError_WhenOutOfBounds)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Core::PencilTool pencilTool{ canvas };
        PixelPad::Core::DrawCommand drawCommand1{ -1, -1, 123, true };
        PixelPad::Core::DrawCommand drawCommand2{ 10, 10, 25, true };

        EXPECT_NO_THROW(pencilTool.Draw(drawCommand1));
        EXPECT_NO_THROW(pencilTool.Draw(drawCommand2));
    }

    TEST(PencilToolTests, Draw_ShouldUpdateMultiplePixels_WhenMultipleCallsAreMade)
    {
        PixelPad::Core::Canvas canvas{ 6, 6, 0 };
        PixelPad::Core::PencilTool pencilTool{ canvas };

        pencilTool.Draw({ 1, 1, 200, true });
        pencilTool.Draw({ 1, 1, 200, false });

        pencilTool.Draw({ 2, 2, 190, true });
        pencilTool.Draw({ 2, 2, 190, false });

        pencilTool.Draw({ 3, 3, 18, true });
        pencilTool.Draw({ 3, 3, 18, false });

        EXPECT_EQ(canvas.GetPixel(1, 1), 200);
        EXPECT_EQ(canvas.GetPixel(2, 2), 190);
        EXPECT_EQ(canvas.GetPixel(3, 3), 18);
    }

    TEST(PencilToolTests, Draw_ShouldNotThrowError_WhenNegativeCoordinatesArePassed)
    {
        PixelPad::Core::Canvas canvas{ 6, 6, 0 };
        PixelPad::Core::PencilTool pencilTool{ canvas };
        PixelPad::Core::DrawCommand drawCommand{ -1, -1, 240, true };

        EXPECT_NO_THROW(pencilTool.Draw(drawCommand));
    }

    TEST(PencilToolTests, Draw_ShouldOverwritePixelColor_WhenPixelIsAlreadyColored)
    {
        PixelPad::Core::Canvas canvas{ 6, 6, 0 };
        PixelPad::Core::PencilTool pencilTool{ canvas };
        PixelPad::Core::DrawCommand drawCommand1{ 1, 1, 2, true };
        PixelPad::Core::DrawCommand drawCommand2{ 1, 1, 100, true };

        pencilTool.Draw(drawCommand1);
        pencilTool.Draw(drawCommand2);

        EXPECT_EQ(canvas.GetPixel(drawCommand2.X, drawCommand2.Y), drawCommand2.Color);
    }

    TEST(PencilToolTests, Draw_ShouldSetPixelColor_WhenMinEdgeCoordinatesAreUsed)
    {
        PixelPad::Core::Canvas canvas{ 1, 1, 0 };
        PixelPad::Core::PencilTool pencilTool{ canvas };
        PixelPad::Core::DrawCommand drawCommand{ 0, 0, 200, true };

        pencilTool.Draw(drawCommand);

        EXPECT_EQ(canvas.GetPixel(drawCommand.X, drawCommand.Y), drawCommand.Color);
    }

    TEST(PencilToolTests, Draw_ShouldSetPixelColor_WhenMaxEdgeCoordinatesAreUsed)
    {
        PixelPad::Core::Canvas canvas{ 5, 5, 0 };
        PixelPad::Core::PencilTool pencilTool{ canvas };
        PixelPad::Core::DrawCommand drawCommand{ 4, 4, 155, true };

        pencilTool.Draw(drawCommand);

        EXPECT_EQ(canvas.GetPixel(drawCommand.X, drawCommand.Y), drawCommand.Color);
    }
}