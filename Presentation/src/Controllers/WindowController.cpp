#include "Controllers/WindowController.hpp"
#include "Windows/IWindow.hpp"
#include "Buses/EventBus.hpp"
#include "Events/WindowCloseEvent.hpp"
#include <Events/WindowResizeEvent.hpp>

namespace PixelPad::Presentation
{
	WindowController::WindowController(PixelPad::Infrastructure::IWindow& window, PixelPad::Infrastructure::EventBus& m_eventBus) :
		m_window(window),
		m_eventBus(m_eventBus),
		m_windowCloseEventToken(),
		m_windowResizeEventToken()
	{
		RegisterEventHandlers();
	}

	void WindowController::RegisterEventHandlers()
	{
		m_windowCloseEventToken = m_eventBus.Subscribe<PixelPad::Application::WindowCloseEvent>
			([this](const PixelPad::Application::WindowCloseEvent&)
			{
				m_window.Close();
			});

		m_windowResizeEventToken = m_eventBus.Subscribe<PixelPad::Application::WindowResizeEvent>(
			[this](const PixelPad::Application::WindowResizeEvent& evt)
			{
				m_window.Resize(evt.Width, evt.Height);
			});
	}

	WindowController::~WindowController()
	{
		UnregisterEventHandlers();
	}

	void WindowController::UnregisterEventHandlers()
	{
		m_eventBus.Unsubscribe<PixelPad::Application::WindowCloseEvent>(m_windowCloseEventToken);
		m_eventBus.Unsubscribe<PixelPad::Application::WindowResizeEvent>(m_windowResizeEventToken);
	}

	void WindowController::Resize(int newWidth, int newHeight)
	{
		m_window.Resize(newWidth, newHeight);
	}

	void WindowController::Close()
	{
		m_window.Close();
	}

	bool WindowController::IsOpen() const
	{
		return m_window.IsOpen();
	}
} 