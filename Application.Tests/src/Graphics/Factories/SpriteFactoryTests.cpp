#include <gtest/gtest.h>
#include "Graphics/Factories/SpriteFactory.hpp"
#include "Graphics/ITextureManager.hpp"
#include "Graphics/ITexture.hpp"
#include "Geometries/Transform.hpp"
#include "Graphics/ISprite.hpp"
#include "Graphics/IButtonSprite.hpp"
#include "Graphics/Color.hpp"

namespace PixelPad::Tests::Application
{
    struct TestTexture : public PixelPad::Application::ITexture
    {
        int GetWidth() const override { return 100; }
        int GetHeight() const override { return 50; }
    };

    struct TestTextureManager : public PixelPad::Application::ITextureManager
    {
        std::shared_ptr<PixelPad::Application::ITexture> LoadTexture(const std::string& path) override
        {
            return std::make_shared<TestTexture>();
        }

        std::shared_ptr<PixelPad::Application::ITexture> LoadTexture(PixelPad::Core::Color color) override
        {
            return std::make_shared<TestTexture>();
        }
    };

    TEST(SpriteFactoryTests, CreateSprite_ShouldReturnSprite_WhenCalled)
    {
        TestTextureManager testTextureManager;
        PixelPad::Application::SpriteFactory spriteFactory{ testTextureManager };
        PixelPad::Core::Transform transform{ 20, 30, 1, 200, 200 };

        auto sprite = spriteFactory.CreateSprite("test", transform);
        auto texture = sprite->GetTexture();

        ASSERT_NE(sprite, nullptr); 
        EXPECT_EQ(sprite->GetWidth(), transform.Width);
        EXPECT_EQ(sprite->GetHeight(), transform.Height);
        EXPECT_EQ(sprite->GetXCoordinate(), transform.X);
        EXPECT_EQ(sprite->GetYCoordinate(), transform.Y);
        EXPECT_EQ(sprite->GetZCoordinate(), transform.Z);
        ASSERT_NE(texture, nullptr);
        EXPECT_EQ(texture->GetWidth(), 100);
        EXPECT_EQ(texture->GetHeight(), 50);
    }

    TEST(SpriteFactoryTests, CreateButtonSprite_ShouldReturnButtonSprite_WhenCalled)
    {
        TestTextureManager testTextureManager;
        PixelPad::Application::SpriteFactory spriteFactory{ testTextureManager };
        PixelPad::Core::Transform transform{ 20, 30, 1, 200, 200 };

        auto buttonSprite = spriteFactory.CreateButtonSprite("unClickPath","clickedPath", transform);
        auto texture = buttonSprite->GetTexture();

        ASSERT_NE(buttonSprite, nullptr);
        EXPECT_EQ(buttonSprite->GetWidth(), transform.Width);
        EXPECT_EQ(buttonSprite->GetHeight(), transform.Height);
        EXPECT_EQ(buttonSprite->GetXCoordinate(), transform.X);
        EXPECT_EQ(buttonSprite->GetYCoordinate(), transform.Y);
        EXPECT_EQ(buttonSprite->GetZCoordinate(), transform.Z);
        ASSERT_NE(texture, nullptr);
        EXPECT_EQ(texture->GetWidth(), 100);
        EXPECT_EQ(texture->GetHeight(), 50);
    }
}