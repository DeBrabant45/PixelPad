#include "gtest/gtest.h"
#include "Graphics/Color.hpp"

namespace PixelPad::Tests::Core
{
    TEST(ColorTests, Constructor_ShouldDefault_WhenNoValuesAreSupplied) 
    {
        PixelPad::Core::Color color;

        EXPECT_EQ(color.R, 0);
        EXPECT_EQ(color.G, 0);
        EXPECT_EQ(color.B, 0);
        EXPECT_EQ(color.A, 255);
    }

    TEST(ColorTests, Constructor_ShouldSupplyGivenValues_WhenValuesAreSupplied)
    {
        auto expectedRed = 10;
        auto expectedGreen = 20;
        auto expectedBlue = 30;
        auto expectedAlpha = 40;

        PixelPad::Core::Color color(
            expectedRed, expectedGreen, expectedBlue, expectedAlpha);

        EXPECT_EQ(color.R, expectedRed);
        EXPECT_EQ(color.G, expectedGreen);
        EXPECT_EQ(color.B, expectedBlue);
        EXPECT_EQ(color.A, expectedAlpha);
    }

    TEST(ColorTests, ToRGBA_ShouldReturnCorrectPackedValue_WhenValuesAreSupplied)
    {
        PixelPad::Core::Color color(0x11, 0x22, 0x33, 0x44);

        auto rgba = color.ToRGBA();

        EXPECT_EQ(rgba, 0x11223344u);
    }

    TEST(ColorTests, EqualityOperator_ShouldReturnTrue_WhenComparisonAreEqual)
    {
        PixelPad::Core::Color a(1, 2, 3, 4);
        PixelPad::Core::Color b(1, 2, 3, 4);

        EXPECT_TRUE(a == b);
    }

    TEST(ColorTests, EqualityOperator_ShouldReturnFalse_WhenComparisionAreNotEqual)
    {
        PixelPad::Core::Color a(1, 2, 3, 4);
        PixelPad::Core::Color b(1, 3, 3, 4);

        EXPECT_FALSE(a == b);
    }
}