#include <gtest/gtest.h>
#include "Tools/Toolbox.hpp"

namespace PixelPad::Tests::Application
{
    TEST(ToolboxTests, Constructor_Should_NotThrow)
    {
        PixelPad::Core::Canvas canvas{ 8, 6, 0 };
        EXPECT_NO_THROW({
            PixelPad::Application::Toolbox toolbox{ canvas };
            });
    }

    TEST(ToolboxTests, GetTool_Should_ReturnValidReference_ForEachToolType)
    {
        PixelPad::Core::Canvas canvas{ 8, 6, 0 };
        PixelPad::Application::Toolbox toolbox{ canvas };

        auto& pencilTool = toolbox.GetTool(PixelPad::Application::ToolType::Pencil);
        auto& lineTool = toolbox.GetTool(PixelPad::Application::ToolType::Line);
        auto& fillTool = toolbox.GetTool(PixelPad::Application::ToolType::Fill);

        EXPECT_NE(&pencilTool, nullptr);
        EXPECT_NE(&lineTool, nullptr);
        EXPECT_NE(&fillTool, nullptr);
    }

    TEST(ToolboxTests, GetTool_Should_Throw_WhenInvalidToolType)
    {
        PixelPad::Core::Canvas canvas{ 8, 6, 0 };
        PixelPad::Application::Toolbox toolbox{ canvas };

        EXPECT_THROW(
            toolbox.GetTool(static_cast<PixelPad::Application::ToolType>(999)),
            std::runtime_error
        );
    }

    TEST(ToolboxTests, GetTool_Should_ReturnDistinctInstances_ForDifferentToolTypes)
    {
        PixelPad::Core::Canvas canvas{ 8, 6, 0 };
        PixelPad::Application::Toolbox toolbox{ canvas };

        auto& pencilTool = toolbox.GetTool(PixelPad::Application::ToolType::Pencil);
        auto& lineTool = toolbox.GetTool(PixelPad::Application::ToolType::Line);

        EXPECT_NE(&pencilTool, &lineTool);
    }
}