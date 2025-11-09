#include "gtest/gtest.h"
#include "Buses/EventBus.hpp"
#include "Graphics/IButtonSprite.hpp"
#include "Graphics/ITexture.hpp"
#include <Events/UIButtonClickedEvent.hpp>
#include <Graphics/Factories/ISpriteFactory.hpp>
#include <Graphics/UIButton.hpp>

namespace PixelPad::Tests::Infrastructure
{
    class DummyButtonSprite : public PixelPad::Application::IButtonSprite
    {
    public:
        std::shared_ptr<PixelPad::Application::ITexture> GetTexture() override { return nullptr; }
        int GetWidth() const override { return 11; }
        int GetHeight() const override { return 12; }
        int GetXCoordinate() const override { return 50; }
        int GetYCoordinate() const override { return 30; }
        int GetZCoordinate() const override { return 2; }
        void SetState(PixelPad::Application::ButtonState state) override {  }
    };

    TEST(UIButtonTests, OnClick_ShouldPublishesEvent_WhenClickWithinBounds)
    {
        PixelPad::Infrastructure::EventBus eventBus;
        PixelPad::Core::Transform transform{ 10, 10, 100, 50, 40 };
        auto sprite = std::make_unique<DummyButtonSprite>();
        bool eventReceived = false;
        int receivedValue = 0;
        eventBus.Subscribe<PixelPad::Application::UIButtonClickedEvent<int>>(
            [&](const PixelPad::Application::UIButtonClickedEvent<int>& evt)
            {
                eventReceived = true;
                receivedValue = evt.Value;
            });
        PixelPad::Infrastructure::UIButton<int> button(transform, std::move(sprite), eventBus, 42);

        button.OnClick(12, 13);

        EXPECT_TRUE(eventReceived);
        EXPECT_EQ(receivedValue, 42);
    }

    TEST(UIButtonTests, OnClick_ShouldNotPublishesEvent_WhenClickIsOutsideBounds)
    {
        PixelPad::Infrastructure::EventBus eventBus;
        PixelPad::Core::Transform transform{ 12, 11, 100, 10, 10 };
        auto sprite = std::make_unique<DummyButtonSprite>();
        bool eventReceived = false;
        int receivedValue = 0;
        eventBus.Subscribe<PixelPad::Application::UIButtonClickedEvent<int>>(
            [&](const PixelPad::Application::UIButtonClickedEvent<int>& evt)
            {
                eventReceived = true;
                receivedValue = evt.Value;
            });
        PixelPad::Infrastructure::UIButton<int> button(transform, std::move(sprite), eventBus, 42);

        button.OnClick(200, 50);

        EXPECT_FALSE(eventReceived);
    }
}