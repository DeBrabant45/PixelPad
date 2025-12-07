#include "Graphics/UIToolsPanel.hpp"
#include <Graphics/IUIRoot.hpp>
#include "Graphics/IUIButton.hpp"

namespace PixelPad::Infrastructure
{
	UIToolsPanel::UIToolsPanel(PixelPad::Application::ISpriteFactory& spriteFactory, PixelPad::Infrastructure::EventBus& eventBus) :
		m_spriteFactory(spriteFactory),
        m_eventBus(eventBus)
	{
		CreateToolButtons(eventBus);
        RegisterEventHandlers();
	}

    void UIToolsPanel::RegisterEventHandlers()
    {
        m_buttonIdToken = m_eventBus.Subscribe<
            PixelPad::Application::UIButtonClickedEvent<PixelPad::Application::ClickResult>>(
                [this](const PixelPad::Application::UIButtonClickedEvent<PixelPad::Application::ClickResult>& evt)
                {
                    auto buttonId = evt.Value.ButtonId;
                    SetActiveButton(buttonId);
                });

    }

    UIToolsPanel::~UIToolsPanel()
    {
        UnregisterEventHandlers();
    }

    void UIToolsPanel::UnregisterEventHandlers()
    {
        m_eventBus.Unsubscribe<
            PixelPad::Application::UIButtonClickedEvent<PixelPad::Application::ClickResult>>(m_buttonIdToken);
    }

    void UIToolsPanel::CreateToolButtons(PixelPad::Infrastructure::EventBus& eventBus)
    {
        struct ButtonInfo
        {
            PixelPad::Core::ToolType Tool;
            std::string Texture;
            std::string OutlineTexture;
        };

        std::vector<ButtonInfo> buttonNames = 
        {
            {PixelPad::Core::ToolType::Pencil,    "pencil.bmp",        "pencil-outline.bmp"},
            {PixelPad::Core::ToolType::Eraser,    "eraser.bmp",        "eraser-outline.bmp"},
            {PixelPad::Core::ToolType::Fill,      "paint-bucket.bmp",  "paint-bucket-outline.bmp"},
            {PixelPad::Core::ToolType::Line,      "line-tool.bmp",     "line-tool-outline.bmp"},
            {PixelPad::Core::ToolType::Rectangle, "rectangle-tool.bmp","rectangle-tool-outline.bmp"},
            {PixelPad::Core::ToolType::Ellipse,   "ellipse-tool.bmp",  "ellipse-tool-outline.bmp"},
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
                buttonNames[i].Texture,
                buttonNames[i].OutlineTexture,
                transform
            );

            auto button = std::make_unique<PixelPad::Infrastructure::UIButton<PixelPad::Core::ToolType>>(
                transform,
                std::move(sprite),
                eventBus,
                buttonNames[i].Tool
            );

            if (buttonNames[i].Tool == PixelPad::Core::ToolType::Pencil)
            {
                button->SetActive(true);
            }

            m_buttons.emplace_back(std::move(button));
        }
    }

    void UIToolsPanel::SetActiveButton(std::uint32_t id)
    {
        if (!OwnsButton(id))
            return;

        for (auto& button : m_buttons)
        {
            button->SetActive(button->GetId() == id);
        }
    }

    bool UIToolsPanel::OwnsButton(std::uint32_t id)
    {
        for (auto& button : m_buttons)
        {
            if (button->GetId() == id)
                return true;
        }

        return false;
    }

	void UIToolsPanel::Render(PixelPad::Application::IRenderer& renderer)
	{
		for (auto& button : m_buttons)
		{
			button->Render(renderer);
		}
	}
}