#include <gtest/gtest.h>
#include "Graphics/ButtonSprite.hpp"
#include "Graphics/ITexture.hpp"
#include "Geometries/Transform.hpp"

#include <memory>

namespace PixelPad::Tests::Application
{
    struct TestTexture : public PixelPad::Application::ITexture
    {
        const int Width;
        const int Height;

        TestTexture(int width, int height) : 
            Width(width), 
            Height(height)
        {

        }

        int GetWidth() const override { return Width; }
        int GetHeight() const override { return Height; }
    };

    TEST(ButtonSprite, SetState_ShouldSetTextureToUnClicked_WhenPassingUnclickedState)
    {
        auto buttonSpriteTexture = PixelPad::Application::ButtonSpriteTexture
        {
            std::make_shared<TestTexture>(10, 10), // UnClicked
            std::make_shared<TestTexture>(11, 11), // Clicked
            std::make_shared<TestTexture>(12, 12)  // Hover
        };
        auto sut = PixelPad::Application::ButtonSprite(PixelPad::Core::Transform(0, 0, 0, 10, 10), buttonSpriteTexture);

        sut.SetState(PixelPad::Application::ButtonState::UnClicked);

        EXPECT_EQ(sut.GetTexture(), buttonSpriteTexture.UnClicked);
    }

    TEST(ButtonSprite, SetState_ShouldSetTextureToClicked_WhenPassingClickedState)
    {
        auto buttonSpriteTexture = PixelPad::Application::ButtonSpriteTexture
        {
            std::make_shared<TestTexture>(10, 10), // UnClicked
            std::make_shared<TestTexture>(11, 11), // Clicked
            std::make_shared<TestTexture>(12, 12)  // Hover
        };
        auto sut = PixelPad::Application::ButtonSprite(PixelPad::Core::Transform(0, 0, 0, 10, 10), buttonSpriteTexture);

        sut.SetState(PixelPad::Application::ButtonState::Clicked);

        EXPECT_EQ(sut.GetTexture(), buttonSpriteTexture.Clicked);
    }

    TEST(ButtonSprite, SetState_ShouldSetTextureToHover_WhenPassingHoverState)
    {
        auto buttonSpriteTexture = PixelPad::Application::ButtonSpriteTexture
        {
            std::make_shared<TestTexture>(10, 10), // UnClicked
            std::make_shared<TestTexture>(11, 11), // Clicked
            std::make_shared<TestTexture>(12, 12)  // Hover
        };
        auto sut = PixelPad::Application::ButtonSprite(PixelPad::Core::Transform(0, 0, 0, 10, 10), buttonSpriteTexture);

        sut.SetState(PixelPad::Application::ButtonState::Hover);

        EXPECT_EQ(sut.GetTexture(), buttonSpriteTexture.Hover);
    }
}