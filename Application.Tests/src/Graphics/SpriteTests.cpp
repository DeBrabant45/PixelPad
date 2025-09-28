#include <gtest/gtest.h>
#include "Graphics/Sprite.hpp"
#include "Graphics/ITexture.hpp"

#include <memory>

namespace PixelPad::Tests::Application
{
    struct TestTexture : public PixelPad::Application::ITexture
    {
        int GetWidth() const override { return 100; }
        int GetHeight() const override { return 50; }
    };

    TEST(SpriteTests, GetWidth_ShouldReturnBackPassedInValue_WhenCalled)
    {
        auto expectedWidth = 30;
        auto texture = std::make_shared<TestTexture>();

        auto sut = PixelPad::Application::Sprite(expectedWidth, 10, 0, 0, texture);

        EXPECT_EQ(sut.GetWidth(), expectedWidth);
    }

    TEST(SpriteTests, GetHeight_ShouldReturnBackPassedInValue_WhenCalled)
    {
        auto expectedHeight = 50;
        auto texture = std::make_shared<TestTexture>();

        auto sut = PixelPad::Application::Sprite(10, expectedHeight, 0, 0, texture);

        EXPECT_EQ(sut.GetHeight(), expectedHeight);
    }

    TEST(SpriteTests, GetXCoordinate_ShouldReturnBackPassedInValue_WhenCalled)
    {
        auto expectedXCoordinate = 60;
        auto texture = std::make_shared<TestTexture>();

        auto sut = PixelPad::Application::Sprite(10, 10, expectedXCoordinate, 0, texture);

        EXPECT_EQ(sut.GetXCoordinate(), expectedXCoordinate);
    }

    TEST(SpriteTests, GetYCoordinate_ShouldReturnBackPassedInValue_WhenCalled)
    {
        auto expectedYCoordinate = 70;
        auto texture = std::make_shared<TestTexture>();

        auto sut = PixelPad::Application::Sprite(10, 10, 4, expectedYCoordinate, texture);

        EXPECT_EQ(sut.GetYCoordinate(), expectedYCoordinate);
    }

    TEST(SpriteTests, GetTexture_ShouldReturnBackPassedInValue_WhenCalled)
    {
        auto expectedTexture = std::make_shared<TestTexture>();

        auto sut = PixelPad::Application::Sprite(10, 10, 4, 80, expectedTexture);
        auto texture = sut.GetTexture();

        EXPECT_EQ(texture, expectedTexture);
        EXPECT_EQ(texture.get()->GetHeight(), expectedTexture.get()->GetHeight());
        EXPECT_EQ(texture.get()->GetWidth(), expectedTexture.get()->GetWidth());
    }
}