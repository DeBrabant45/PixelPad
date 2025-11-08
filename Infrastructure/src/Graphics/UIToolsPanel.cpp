#include "Graphics/UIToolsPanel.hpp"
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
        std::vector<std::pair<PixelPad::Core::ToolType, std::string>> buttonNames = {
            {PixelPad::Core::ToolType::Pencil, "pencil.bmp"},
            {PixelPad::Core::ToolType::Eraser, "eraser.bmp"},
            {PixelPad::Core::ToolType::Fill, "paint-bucket.bmp"},
            {PixelPad::Core::ToolType::Line, "line-tool.bmp"},
            {PixelPad::Core::ToolType::Rectangle, "rectangle-tool.bmp"},
            {PixelPad::Core::ToolType::Ellipse, "ellipse-tool.bmp"},
        };

        int startX = 4;
        int startY = 40;
        int size = 28;
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

            m_buttons.emplace_back(std::make_unique<PixelPad::Infrastructure::UIButton<PixelPad::Core::ToolType>>(
                transform,
                std::move(sprite),
                eventBus,
                buttonNames[i].first
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