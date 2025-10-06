#include "Graphics/UIToolsPanel.hpp"
#include <Events/ToolTypeChangedEvent.hpp>
#include <Graphics/IUIRoot.hpp>
#include "Graphics/IUIButton.hpp"

namespace PixelPad::Infrastructure
{
	UIToolsPanel::UIToolsPanel(PixelPad::Application::ISpriteFactory& spriteFactory, PixelPad::Infrastructure::EventBus& eventBus) :
		m_spriteFactory(spriteFactory)
	{
		CreateToolButtons(eventBus);
	}

    void UIToolsPanel::CreateToolButtons(PixelPad::Infrastructure::EventBus& eventBus)
    {
        std::vector<std::pair<std::string, std::string>> buttonNames = {
            {"PencilTool", "../Assets/pencil.bmp"},
            {"EraserTool", "C:/Assets/sample.bmp"},
            {"FillTool", "C:/Assets/sample.bmp"},
            {"LineTool", "C:/Assets/sample.bmp"},
            {"RectangleTool", "C:/Assets/sample.bmp"},
            {"EllipseTool", "C:/Assets/sample.bmp"},
        };

        int startX = 0;
        int startY = 40;
        int size = 32;
        int spacing = 6;

        for (int i = 0; i < buttonNames.size(); i++)
        {
            int row = i / 2;
            int col = i % 2;

            PixelPad::Core::Transform transform(
                startX + col * (size + spacing),
                startY + row * (size + spacing),
                1, 
                size,
                size
            );

            auto sprite = m_spriteFactory.CreateButtonSprite(
                buttonNames[i].second, 
                buttonNames[i].second, 
                buttonNames[i].second, 
                transform
            );

            m_buttons.emplace_back(std::make_unique<PixelPad::Infrastructure::UIButton>(
                buttonNames[i].first,
                transform,
                std::move(sprite),
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