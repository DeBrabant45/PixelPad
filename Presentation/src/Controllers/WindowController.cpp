#include "Controllers/WindowController.hpp"
#include "Windows/IWindow.hpp"
#include "Buses/EventBus.hpp"
#include "Events/WindowCloseEvent.hpp"

namespace PixelPad::Presentation
{
	WindowController::WindowController(PixelPad::Infrastructure::IWindow& window, PixelPad::Infrastructure::EventBus& m_eventBus) :
		m_window(window),
		m_eventBus(m_eventBus)
	{
		RegisterEventHandlers();
	}

	void WindowController::RegisterEventHandlers()
	{
		m_windowCloseEventToken = m_eventBus.Subscribe<PixelPad::Infrastructure::WindowCloseEvent>
			([this](const PixelPad::Infrastructure::WindowCloseEvent&)
			{
				m_window.Close();
			});
	}

	WindowController::~WindowController()
	{
		UnregisterEventHandlers();
	}

	void WindowController::UnregisterEventHandlers()
	{
		m_eventBus.Unsubscribe<PixelPad::Infrastructure::WindowCloseEvent>(m_windowCloseEventToken);
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