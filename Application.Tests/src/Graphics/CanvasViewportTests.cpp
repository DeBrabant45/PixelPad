#include <gtest/gtest.h>
#include "Graphics/CanvasViewport.hpp"

#include <utility>

namespace PixelPad::Tests::Application
{
    TEST(CanvasViewportTests, GetWidth_ShouldReturnBackPassedInValue_WhenCalled)
    {
        auto expectedWidth = 30;

        auto sut = PixelPad::Application::CanvasViewport(expectedWidth, 10, 0, 0);

        EXPECT_EQ(sut.GetWidth(), expectedWidth);
    }

    TEST(CanvasViewportTests, GetHeight_ShouldReturnBackPassedInValue_WhenCalled)
    {
        auto expectedHeight = 50;

        auto sut = PixelPad::Application::CanvasViewport(10, expectedHeight, 0, 0);

        EXPECT_EQ(sut.GetHeight(), expectedHeight);
    }

    TEST(CanvasViewportTests, GetXOffset_ShouldReturnBackPassedInValue_WhenCalled)
    {
        auto expectedXOffSet = 60;

        auto sut = PixelPad::Application::CanvasViewport(10, 10, expectedXOffSet, 0);

        EXPECT_EQ(sut.GetXOffset(), expectedXOffSet);
    }

    TEST(CanvasViewportTests, GetYOffset_ShouldReturnBackPassedInValue_WhenCalled)
    {
        auto expectedYOffSet = 70;

        auto sut = PixelPad::Application::CanvasViewport(10, 10, 4, expectedYOffSet);

        EXPECT_EQ(sut.GetYOffset(), expectedYOffSet);
    }

    TEST(CanvasViewportTests, Contains_ShouldReturnTrue_WhenCoordinatesAreWithinBoundaries)
    {
        auto sut = PixelPad::Application::CanvasViewport(50, 50, 10, 8);

        EXPECT_EQ(sut.Contains(15, 9), true);
    }

    TEST(CanvasViewportTests, Contains_ShouldReturnFalse_WhenCoordinatesAreNotWithinBoundaries)
    {
        auto sut = PixelPad::Application::CanvasViewport(20, 20, 10, 8);

        EXPECT_EQ(sut.Contains(9, 7), false);
    }

    TEST(CanvasViewportTests, Contains_ShouldReturnTrue_WhenCoordinatesAtMaxLimitsOfBounrdaries)
    {
        auto sut = PixelPad::Application::CanvasViewport(12, 12, 5, 5);

        EXPECT_EQ(sut.Contains(6, 6), true);
    }

    TEST(CanvasViewportTests, Contains_ShouldReturnTrue_WhenCoordinatesAtMinLimitsOfBounrdaries)
    {
        auto sut = PixelPad::Application::CanvasViewport(12, 12, 2, 3);

        EXPECT_EQ(sut.Contains(2, 3), true);
    }

    TEST(CanvasViewportTests, Contains_ShouldReturnTrue_WhenCoordinatesAreWithinBoundariesAndNegativeValues)
    {
        auto sut = PixelPad::Application::CanvasViewport(18, 16, -5, -6);

        EXPECT_EQ(sut.Contains(-4, -2), true);
    }

    TEST(CanvasViewportTests, ToLocal_ShouldReturnPairedValue_WhenCoordinatesArePassedIn)
    {
        int xOffset = 10;
        int yOffset = 11;
        int xCoordinate = 2;
        int yCoordinate = 3;
        auto expectedPair = std::pair<int, int>(xCoordinate - xOffset, yCoordinate - yOffset);

        auto sut = PixelPad::Application::CanvasViewport(25, 25, xOffset, yOffset);
        auto local = sut.ToLocal(xCoordinate, yCoordinate);

        EXPECT_EQ(local, expectedPair);
    }

    TEST(CanvasViewportTests, ToLocal_ShouldReturnPairedValue_WhenNegativeCoordinatesPassedIn)
    {
        int xOffset = 10;
        int yOffset = 11;
        int xCoordinate = -5;
        int yCoordinate = -9;
        auto expectedPair = std::pair<int, int>(xCoordinate - xOffset, yCoordinate - yOffset);

        auto sut = PixelPad::Application::CanvasViewport(25, 25, xOffset, yOffset);
        auto local = sut.ToLocal(xCoordinate, yCoordinate);

        EXPECT_EQ(local, expectedPair);
    }
}