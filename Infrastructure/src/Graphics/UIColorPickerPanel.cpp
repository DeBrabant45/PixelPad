#include "Graphics/UIColorPickerPanel.hpp"
#include "Graphics/Color.hpp"

namespace PixelPad::Infrastructure
{
	UIColorPickerPanel::UIColorPickerPanel(PixelPad::Application::ISpriteFactory& spriteFactory, PixelPad::Infrastructure::EventBus& eventBus) :
		m_spriteFactory(spriteFactory),
		m_buttons()
	{
		CreateButtons(eventBus);
	}

    void UIColorPickerPanel::CreateButtons(PixelPad::Infrastructure::EventBus& eventBus)
    {
        std::vector<PixelPad::Core::Color> colors = {
            // First row
            PixelPad::Core::Color(0, 0, 0),       // Black
            PixelPad::Core::Color(128, 128, 128), // Dark Gray
            PixelPad::Core::Color(192, 192, 192), // Light Gray
            PixelPad::Core::Color(255, 255, 255), // White
            PixelPad::Core::Color(128, 0, 0),     // Maroon
            PixelPad::Core::Color(255, 0, 0),     // Red
            PixelPad::Core::Color(255, 128, 128), // Light Red
            PixelPad::Core::Color(128, 64, 0),    // Brown
            PixelPad::Core::Color(255, 128, 0),   // Orange
            PixelPad::Core::Color(255, 255, 0),   // Yellow
            PixelPad::Core::Color(128, 128, 0),   // Olive
            PixelPad::Core::Color(0, 128, 0),     // Dark Green
            PixelPad::Core::Color(0, 255, 0),     // Lime

            // Second row
            PixelPad::Core::Color(0, 255, 255),   // Cyan
            PixelPad::Core::Color(0, 0, 128),     // Navy
            PixelPad::Core::Color(0, 0, 255),     // Blue
            PixelPad::Core::Color(128, 128, 255), // Light Blue
            PixelPad::Core::Color(128, 0, 128),   // Purple
            PixelPad::Core::Color(255, 0, 255),   // Magenta
            PixelPad::Core::Color(255, 128, 255), // Light Magenta
            PixelPad::Core::Color(64, 64, 64),    // Dark Gray 2
            PixelPad::Core::Color(192, 64, 0),    // Brownish Orange
            PixelPad::Core::Color(255, 192, 0),   // Gold
            PixelPad::Core::Color(0, 64, 0),      // Dark Green 2
            PixelPad::Core::Color(0, 255, 128),   // Bright Green
            PixelPad::Core::Color(0, 128, 128),   // Teal
        };

        int startX = 40;
        int startY = 545;
        int size = 13;
        int spacing = 3;
        int rows = 2;      
        int cols = (colors.size() + rows - 1) / rows;

        for (size_t i = 0; i < colors.size(); ++i)
        {
            int row = i / cols;
            int col = i % cols;

            PixelPad::Core::Transform transform
            (
                startX + col * (size + spacing),
                startY + row * (size + spacing),
                1,
                size,
                size
            );

            auto sprite = m_spriteFactory.CreateButtonSprite(colors[i], transform);

            m_buttons.emplace_back(std::make_unique<PixelPad::Infrastructure::UIButton<PixelPad::Core::Color>>(
                transform,
                std::move(sprite),
                eventBus,
                colors[i]
            ));
        }
    }

	void UIColorPickerPanel::Render(PixelPad::Application::IRenderer& renderer)
	{
		for (auto& button : m_buttons)
		{
			button->Render(renderer);
		}
	}
}