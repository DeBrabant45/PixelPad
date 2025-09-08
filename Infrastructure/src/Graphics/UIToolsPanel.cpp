#include "Graphics/UIToolsPanel.hpp"
#include <Events/ToolTypeChangedEvent.hpp>
#include <Graphics/IUIRoot.hpp>
#include "Graphics/IUIButton.hpp"

namespace PixelPad::Infrastructure
{
	UIToolsPanel::UIToolsPanel(PixelPad::Application::ITextureManager& textureManager, PixelPad::Infrastructure::EventBus& eventBus) :
		m_textureManager(textureManager)
	{
		CreateToolButtons(eventBus);
	}

	void UIToolsPanel::CreateToolButtons(PixelPad::Infrastructure::EventBus& eventBus)
	{
		std::vector<std::pair<std::string, std::string>> buttonNames =
		{
			{"PencilTool", "C:/Assets/sample.bmp"},
			{"EraserTool", "C:/Assets/sample.bmp"},
			{"FillTool", "C:/Assets/sample.bmp"},
			{"LineTool", "C:/Assets/sample.bmp"},
			{"RectangleTool", "C:/Assets/sample.bmp"},
			{"EllipseTool", "C:/Assets/sample.bmp"},
		};

		int startX = 720;
		int startY = 10;
		int size = 32;
		int spacing = 6;

		for (int i = 0; i < buttonNames.size(); i++)
		{
			int row = i / 2;
			int col = i % 2;
			auto texture = m_textureManager.LoadTexture(buttonNames[i].second);
			m_buttons.emplace_back(std::make_unique<PixelPad::Infrastructure::UIButton>(
				buttonNames[i].first,
				startX + col * (size + spacing),
				startY + row * (size + spacing),
				size,
				size,
				texture,
				eventBus
			));
		}
	}

	void UIToolsPanel::Render(PixelPad::Application::IRenderer& renderer)
	{
		for (auto& button : m_buttons)
		{
			button->Render(renderer);
		}
	}
}