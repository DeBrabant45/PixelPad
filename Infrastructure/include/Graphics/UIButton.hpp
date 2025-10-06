#pragma once

#include "Graphics/IUIButton.hpp"
#include "Graphics/ITexture.hpp"
#include "Buses/EventBus.hpp"
#include "Geometries/Transform.hpp"
#include "Graphics/IButtonSprite.hpp"

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
		UIButton(
			std::string name, 
			PixelPad::Core::Transform& transform, 
			std::unique_ptr<PixelPad::Application::IButtonSprite> sprite, 
			PixelPad::Infrastructure::EventBus& eventBus);
		~UIButton() override;
		void Render(PixelPad::Application::IRenderer& renderer) override;
		void OnClick(int clickX, int clickY) override;
		PixelPad::Core::Transform GetTransform() const override;

	private:
		void RegisterEventHandlers();
		void UnregisterEventHandlers();

	private:
		std::string m_name;
		PixelPad::Core::Transform m_transform;
		std::unique_ptr<PixelPad::Application::IButtonSprite> m_sprite;
		PixelPad::Infrastructure::EventBus& m_eventBus;
		PixelPad::Infrastructure::EventBus::SubscriptionToken m_mouseEventToken;
	};
}