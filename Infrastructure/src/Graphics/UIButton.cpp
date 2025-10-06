#include "Graphics/UIButton.hpp"
#include "Renderers/IRenderer.hpp"
#include "Graphics/IUIRoot.hpp"

#include <iostream>
#include <Events/MouseButtonEvent.hpp>
#include <Events/UIButtonClickedEvent.hpp>

namespace PixelPad::Infrastructure
{
	PixelPad::Infrastructure::UIButton::UIButton(
		std::string name, 
		PixelPad::Core::Transform& transform,
		std::unique_ptr<PixelPad::Application::IButtonSprite> sprite,
		PixelPad::Infrastructure::EventBus& eventBus) :
		m_name(name),
		m_transform(transform),
		m_sprite(std::move(sprite)),
		m_eventBus(eventBus)
	{
		RegisterEventHandlers();
	}

	void UIButton::RegisterEventHandlers()
	{
		m_mouseEventToken = m_eventBus.Subscribe<PixelPad::Application::MouseButtonEvent>(
			[this](const PixelPad::Application::MouseButtonEvent& evt)
			{
				if (!evt.IsPressed)
					return;

				OnClick(evt.X, evt.Y);
			});
	}
	 
	void UIButton::OnClick(int clickX, int clickY)
	{
		if (clickX >= m_transform.X && clickX <= m_transform.X + m_transform.Width &&
			clickY >= m_transform.Y && clickY <= m_transform.Y + m_transform.Height)
		{
			m_eventBus.Publish(PixelPad::Application::UIButtonClickedEvent{ m_name });
		}
	}

	UIButton::~UIButton()
	{
		UnregisterEventHandlers();
	}

	void UIButton::UnregisterEventHandlers()
	{
		m_eventBus.Unsubscribe<PixelPad::Application::MouseButtonEvent>(m_mouseEventToken);
	}

	void UIButton::Render(PixelPad::Application::IRenderer& renderer)
	{
		if (!m_sprite->GetTexture().get())
			return;

		renderer.DrawTexture(
			m_sprite->GetTexture().get(),
			m_transform.X,
			m_transform.Y,
			m_transform.Width,
			m_transform.Height
		);
	}

	PixelPad::Core::Transform UIButton::GetTransform() const
	{
		return m_transform;
	}
}