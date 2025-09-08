#include "Graphics/UIToolsPanel.hpp"
#include <Events/ToolTypeChangedEvent.hpp>
#include <Graphics/IUIRoot.hpp>
#include "Graphics/IUIButton.hpp"

namespace PixelPad::Infrastructure
{
	UIToolsPanel::UIToolsPanel(PixelPad::Application::ITextureManager& textureManager, PixelPad::Infrastructure::EventBus& eventBus) :
		m_textureManager(textureManager)
	{
		auto texture = m_textureManager.LoadTexture("C:/Assets/sample.bmp");
		auto pencilButton = new PixelPad::Infrastructure::UIButton("PencilTool", 400, 400, 40, 40, texture, eventBus);

		m_buttons.emplace_back(std::move(pencilButton));

		//int panelX = 720;
		//int panelY = 0;
		//int buttonSize = 32;
		//int spacing = 6;
		//int padding = 10;
		//int numberOfButtons = 8;

		//for (int i = 0; i < numberOfButtons; i++)
		//{
		//	int column = i % 2;
		//	int row = i / 2;

		//	auto button = std::make_unique<PixelPad::Infrastructure::UIButton>(
		//		"Just a Test",
		//		panelX + padding + column * (buttonSize + spacing),
		//		panelY + padding + row * (buttonSize + spacing),
		//		buttonSize,
		//		buttonSize,
		//		texture
		//	);

		//	m_buttons.emplace_back(std::move(button));
		//}
	}

	void UIToolsPanel::Render(PixelPad::Application::IRenderer& renderer)
	{
		for (auto& button : m_buttons)
		{
			button->Render(renderer);
		}
	}
}