#pragma once

#include "Graphics/IUIPanel.hpp"
#include "Graphics/UIButton.hpp"
#include "Graphics/Factories/ISpriteFactory.hpp"
#include "Buses/EventBus.hpp"
#include "Tools/Toolbox.hpp"

#include <array>
#include <memory>
#include <cstdint>

namespace PixelPad::Application
{
	class IRenderer;
}

namespace PixelPad::Infrastructure
{
	class UIToolsPanel : public PixelPad::Application::IUIPanel
	{
	public:
		UIToolsPanel(PixelPad::Application::ISpriteFactory& spriteFactory, PixelPad::Infrastructure::EventBus& eventBus);
		~UIToolsPanel();
		void Render(PixelPad::Application::IRenderer& renderer) override;

	private:
		void RegisterEventHandlers();
		void UnregisterEventHandlers();
		void CreateToolButtons(PixelPad::Infrastructure::EventBus& eventBus);
		void SetActiveButton(std::uint32_t id);
		bool OwnsButton(std::uint32_t id);

	private:
		PixelPad::Application::ISpriteFactory& m_spriteFactory;
		PixelPad::Infrastructure::EventBus& m_eventBus;
		std::vector<std::unique_ptr<PixelPad::Infrastructure::UIButton<PixelPad::Core::ToolType>>> m_buttons;
		PixelPad::Infrastructure::EventBus::SubscriptionToken m_buttonIdToken;
	};
}