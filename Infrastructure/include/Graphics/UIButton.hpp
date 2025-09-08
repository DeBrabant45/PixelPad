#pragma once

#include "Graphics/IUIButton.hpp"
#include "Graphics/ITexture.hpp"
#include "Buses/EventBus.hpp"

#include <memory>
#include <string>

namespace PixelPad::Application
{
	class IRenderer;
}

namespace PixelPad::Infrastructure
{
	class UIButton : public PixelPad::Application::IUIButton
	{
	public:
		UIButton(std::string name, int x, int y, int w, int h, std::shared_ptr<PixelPad::Application::ITexture> texture, PixelPad::Infrastructure::EventBus& eventBus);
		~UIButton() override;
		void Render(PixelPad::Application::IRenderer& renderer) override;
		void OnClick(int clickX, int clickY) override;
		PixelPad::Application::Transform GetTransform() const override;

	private:
		void RegisterEventHandlers();
		void UnregisterEventHandlers();

	private:
		std::string m_name;
		PixelPad::Application::Transform m_transform;
		std::shared_ptr<PixelPad::Application::ITexture> m_texture;
		PixelPad::Infrastructure::EventBus& m_eventBus;
		PixelPad::Infrastructure::EventBus::SubscriptionToken m_mouseEventToken;
	};
}