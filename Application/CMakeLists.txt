# Application Layer

add_library(${PIXEL_PAD_APPLICATION_TARGET_NAME}
    src/Graphics/DrawService.cpp
    include/Graphics/DrawService.hpp

    include/Graphics/IDrawService.hpp
    include/Graphics/IRenderable.hpp
    include/Graphics/ITexture.hpp
    include/Graphics/IUIButton.hpp
    include/Graphics/IUIPanel.hpp
    include/Graphics/IUIRoot.hpp
    include/Graphics/ITextureManager.hpp

    include/Enums/ToolType.hpp
    include/Enums/MouseButton.hpp

    include/Events/MouseButtonEvent.hpp
    include/Events/WindowCloseEvent.hpp
    include/Events/WindowResizeEvent.hpp
    include/Events/ToolTypeChangedEvent.hpp
    include/Events/UIButtonClickedEvent.hpp

    include/Renderers/IRenderer.hpp

    include/Inputs/IInput.hpp

    include/Windows/IWindow.hpp

    include/Tools/IToolbox.hpp

    src/Tools/Toolbox.cpp
    include/Tools/Toolbox.hpp
)

target_include_directories(${PIXEL_PAD_APPLICATION_TARGET_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PIXEL_PAD_APPLICATION_TARGET_NAME}
    PUBLIC
        ${PIXEL_PAD_CORE_TARGET_NAME}
)
