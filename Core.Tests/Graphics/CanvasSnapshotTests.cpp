#include <gtest/gtest.h>
#include "Graphics/Canvas.hpp"
#include "Graphics/CanvasSnapshot.hpp"

namespace PixelPad::Tests::Core
{
    TEST(CanvasSnapshotTests, GetWidth_Should_ReturnCorrectValue)
    {
        int width = 3;
        int height = 2;
        std::vector<int> pixels = { 1, 2, 3, 4, 5, 6 };

        PixelPad::Core::CanvasSnapshot snapshot(width, height, pixels);

        EXPECT_EQ(snapshot.GetWidth(), width);
    }

    TEST(CanvasSnapshotTests, GetHeight_ShouldReturnCorrectValue)
    {
        int width = 3;
        int height = 2;
        std::vector<int> pixels = { 1, 2, 3, 4, 5, 6 };

        PixelPad::Core::CanvasSnapshot snapshot(width, height, pixels);

        EXPECT_EQ(snapshot.GetHeight(), height);
    }

    TEST(CanvasSnapshotTests, GetPixels_ShouldReturnReferenceToInternalData)
    {
        std::vector<int> originalPixels = { 10, 20, 30, 40 };
        PixelPad::Core::CanvasSnapshot snapshot(2, 2, originalPixels);

        const std::vector<int>& retrieved = snapshot.GetPixels();

        EXPECT_EQ(&retrieved, &snapshot.GetPixels());
        EXPECT_EQ(retrieved, originalPixels);
    }

    TEST(CanvasSnapshotTests, Snapshot_ShouldBeImmutableAfterConstruction)
    {
        std::vector<int> originalPixels = { 5, 6, 7, 8 };
        PixelPad::Core::CanvasSnapshot snapshot(2, 2, originalPixels);

        originalPixels[0] = 99;

        EXPECT_EQ(snapshot.GetPixels()[0], 5);
    }

    TEST(CanvasSnapshotTests, ApplyTo_ShouldResizeCanvasAndApplyPixels_WhenCanvasIsBlank)
    {
        std::vector<int> pixels = { 1, 2, 3, 4, 5, 6 };
        PixelPad::Core::CanvasSnapshot snapshot(2, 2, pixels);
        PixelPad::Core::Canvas canvas(10, 10, 0);

        snapshot.ApplyTo(canvas);

        EXPECT_EQ(canvas.GetWidth(), 2);
        EXPECT_EQ(canvas.GetHeight(), 2);
        EXPECT_EQ(canvas.GetPixel(0, 0), 1);
        EXPECT_EQ(canvas.GetPixel(1, 0), 2);
        EXPECT_EQ(canvas.GetPixel(0, 1), 3);
        EXPECT_EQ(canvas.GetPixel(1, 1), 4);
    }

    TEST(CanvasSnapshotTests, ApplyTo_ShouldOverwriteCanvasPixels_WhenCanvasHasExistingData)
    {
        std::vector<int> pixels = { 5, 6, 7, 8 };
        PixelPad::Core::CanvasSnapshot snapshot(2, 2, pixels);
        PixelPad::Core::Canvas canvas(2, 2, 0);

        canvas.DrawPixel(1, 1, 99);
        canvas.DrawPixel(2, 2, 88);
        snapshot.ApplyTo(canvas);

        EXPECT_EQ(canvas.GetPixel(0, 0), 5);
        EXPECT_EQ(canvas.GetPixel(1, 1), 8);
    }

    TEST(CanvasSnapshotTests, ApplyTo_ShouldMaintainPixelOrder_WhenApplyingSnapshot)
    {
        std::vector<int> pixels = { 10, 20, 30, 40 };
        PixelPad::Core::CanvasSnapshot snapshot(2, 2, pixels);
        PixelPad::Core::Canvas canvas(1, 1, 0);

		snapshot.ApplyTo(canvas);

        std::vector<int> result = canvas.GetPixels();
        EXPECT_EQ(result, pixels);
    }

    TEST(CanvasSnapshotTests, ApplyTo_ShouldResizeToZero_WhenSnapshotIsEmpty)
    {
        std::vector<int> emptyPixels;
        PixelPad::Core::CanvasSnapshot snapshot(0, 0, emptyPixels);
        PixelPad::Core::Canvas canvas(2, 2, 0);

		snapshot.ApplyTo(canvas);

        EXPECT_EQ(canvas.GetWidth(), 0);
        EXPECT_EQ(canvas.GetHeight(), 0);
        EXPECT_TRUE(canvas.GetPixels().empty());
    }

    TEST(CanvasSnapshotTests, ApplyTo_ShouldNotModifySnapshot_WhenReusedAcrossMultipleCanvases)
    {
        std::vector<int> pixels = { 1, 2, 3, 4 };
        PixelPad::Core::CanvasSnapshot snapshot(2, 2, pixels);
        PixelPad::Core::Canvas canvasOne(1, 1, 0);
        PixelPad::Core::Canvas canvasTwo(3, 3, 0);

		snapshot.ApplyTo(canvasOne);
		snapshot.ApplyTo(canvasTwo);

        EXPECT_EQ(canvasOne.GetPixels(), pixels);
        EXPECT_EQ(canvasTwo.GetPixels(), pixels);
        EXPECT_EQ(snapshot.GetPixels(), pixels);
    }
}