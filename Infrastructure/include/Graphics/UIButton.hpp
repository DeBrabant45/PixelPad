#pragma once

#include "Graphics/IUIButton.hpp"
#include "Graphics/ITexture.hpp"
#include "Graphics/IUIRoot.hpp"
#include "Buses/EventBus.hpp"
#include "Geometries/Transform.hpp"
#include "Graphics/IButtonSprite.hpp"
#include "Renderers/IRenderer.hpp"
#include "Events/UIButtonClickedEvent.hpp"
#include <Events/MouseButtonEvent.hpp>

#include <iostream>
#include <memory>
#include <string>

namespace PixelPad::Application
{
	class IRenderer;
}

namespace PixelPad::Infrastructure
{
    template<typename TClickEventValue>
    class UIButton : public PixelPad::Application::IUIButton
    {
    public:
        UIButton(
            PixelPad::Core::Transform transform,
            std::unique_ptr<PixelPad::Application::IButtonSprite> sprite,
            PixelPad::Infrastructure::EventBus& eventBus,
            TClickEventValue clickEventValue)
            : m_transform(std::move(transform)),
            m_sprite(std::move(sprite)),
            m_eventBus(eventBus),
            m_clickEventValue(clickEventValue)
        {
            RegisterEventHandlers();
        }

        ~UIButton() override { UnregisterEventHandlers(); }

        void Render(PixelPad::Application::IRenderer& renderer) override
        {
            if (!m_sprite->GetTexture().get())
                return;

            renderer.Render(m_sprite.get());
        }

        void OnClick(int clickX, int clickY) override
        {
            if (clickX >= m_transform.X && clickX <= m_transform.X + m_transform.Width &&
                clickY >= m_transform.Y && clickY <= m_transform.Y + m_transform.Height)
            {
                m_eventBus.Publish(
                    PixelPad::Application::UIButtonClickedEvent<TClickEventValue>(m_clickEventValue));
            }
        }

    private:
        void RegisterEventHandlers()
        {
            m_mouseEventToken = m_eventBus.Subscribe<PixelPad::Application::MouseButtonEvent>(
                [this](const PixelPad::Application::MouseButtonEvent& evt)
                {
                    if (!evt.IsPressed)
                        return;

                    OnClick(evt.X, evt.Y);
                });
        }

        void UnregisterEventHandlers()
        {
            m_eventBus.Unsubscribe<PixelPad::Application::MouseButtonEvent>(m_mouseEventToken);
        }

    private:
        PixelPad::Core::Transform m_transform;
        std::unique_ptr<PixelPad::Application::IButtonSprite> m_sprite;
        PixelPad::Infrastructure::EventBus& m_eventBus;
        TClickEventValue m_clickEventValue;
        PixelPad::Infrastructure::EventBus::SubscriptionToken m_mouseEventToken;
    };
}