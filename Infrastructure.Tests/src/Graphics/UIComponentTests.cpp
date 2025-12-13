#include "gtest/gtest.h"
#include "Graphics/ISprite.hpp"
#include "Graphics/ITexture.hpp"
#include "Graphics/Color.hpp"
#include "Geometries/Transform.hpp"
#include "Graphics/UIComponent.hpp"

namespace PixelPad::Tests::Infrastructure
{
    class DummySprite : public PixelPad::Application::ISprite
    {
    public:
        std::shared_ptr<PixelPad::Application::ITexture> GetTexture() override { return nullptr; }
        int GetWidth() const override { return 11; }
        int GetHeight() const override { return 12; }
        int GetXCoordinate() const override { return 50; }
        int GetYCoordinate() const override { return 30; }
        int GetZCoordinate() const override { return 2; }
    };

    TEST(UIComponentTests, GetTransform_ShouldReturnCorrectTransform)
    {
        PixelPad::Core::Transform transform{ 10, 20, 5, 100, 50 };
        auto sprite = std::make_unique<DummySprite>();

        PixelPad::Infrastructure::UIComponent component(transform, std::move(sprite));
        const auto& returnedTransform = component.GetTransform();

        EXPECT_EQ(returnedTransform.X, transform.X);
        EXPECT_EQ(returnedTransform.Y, transform.Y);
        EXPECT_EQ(returnedTransform.Z, transform.Z);
        EXPECT_EQ(returnedTransform.Width, transform.Width);
        EXPECT_EQ(returnedTransform.Height, transform.Height);
    }
}