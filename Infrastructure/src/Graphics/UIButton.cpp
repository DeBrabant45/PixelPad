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
		int x, 
		int y, 
		int w, 
		int h, 
		std::shared_ptr<PixelPad::Application::ITexture> texture,
		PixelPad::Infrastructure::EventBus& eventBus) :
		m_name(name),
		m_transform{ x, y, w, h },
		m_texture(texture),
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
		if (clickX >= m_transform.x && clickX <= m_transform.x + m_transform.width &&
			clickY >= m_transform.y && clickY <= m_transform.y + m_transform.height)
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
		if (!m_texture)
			return;

		renderer.DrawTexture(
			m_texture.get(),
			m_transform.x,
			m_transform.y,
			m_transform.width,
			m_transform.height
		);
	}

	PixelPad::Application::Transform UIButton::GetTransform() const
	{
		return m_transform;
	}
}