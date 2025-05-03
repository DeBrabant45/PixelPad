#include <gtest/gtest.h>
#include "Graphics/Canvas.hpp"
#include "Graphics/CanvasSnapshot.hpp"

namespace PixelPad::Tests::Core
{
    TEST(CanvasSnapshotTests, GetWidth_ReturnsCorrectValue)
    {
        int width = 3;
        int height = 2;
        std::vector<int> pixels = { 1, 2, 3, 4, 5, 6 };

        PixelPad::Core::CanvasSnapshot snapshot(width, height, pixels);

        EXPECT_EQ(snapshot.GetWidth(), width);
    }

    TEST(CanvasSnapshotTests, GetHeight_ReturnsCorrectValue)
    {
        int width = 3;
        int height = 2;
        std::vector<int> pixels = { 1, 2, 3, 4, 5, 6 };

        PixelPad::Core::CanvasSnapshot snapshot(width, height, pixels);

        EXPECT_EQ(snapshot.GetHeight(), height);
    }

    TEST(CanvasSnapshotTests, GetPixels_ReturnsReferenceToInternalData)
    {
        std::vector<int> originalPixels = { 10, 20, 30, 40 };
        PixelPad::Core::CanvasSnapshot snapshot(2, 2, originalPixels);

        const std::vector<int>& retrieved = snapshot.GetPixels();

        EXPECT_EQ(&retrieved, &snapshot.GetPixels());
        EXPECT_EQ(retrieved, originalPixels);
    }

    TEST(CanvasSnapshotTests, Snapshot_IsImmutableAfterConstruction)
    {
        std::vector<int> originalPixels = { 5, 6, 7, 8 };
        PixelPad::Core::CanvasSnapshot snapshot(2, 2, originalPixels);

        originalPixels[0] = 99;

        EXPECT_EQ(snapshot.GetPixels()[0], 5);
    }
}