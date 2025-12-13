# Infrastructure Layer

add_library(${PIXEL_PAD_INFRASTRUCTURE_TARGET_NAME}
    src/Renderers/SDLRenderer.cpp
    include/Renderers/SDLRenderer.hpp

    src/Windows/SDLWindow.cpp
    include/Windows/SDLWindow.hpp

    src/Inputs/SDLInput.cpp
    include/Inputs/SDLInput.hpp

    src/Buses/EventBus.cpp
    include/Buses/EventBus.hpp

    src/Graphics/SDLTexture.cpp
    include/Graphics/SDLTexture.hpp

    include/Graphics/UIButton.hpp

    src/Graphics/UIRoot.cpp
    include/Graphics/UIRoot.hpp

    src/Graphics/UIToolsPanel.cpp
    include/Graphics/UIToolsPanel.hpp

    src/Graphics/UIColorPickerPanel.cpp
    include/Graphics/UIColorPickerPanel.hpp

    src/Graphics/SDLTextureManager.cpp
    include/Graphics/SDLTextureManager.hpp

    include/Paths/IPathProvider.hpp
    include/Paths/AssetPathProvider.hpp
    src/Paths/AssetPathProvider.cpp

    src/Graphics/UIComponent.cpp
    include/Graphics/UIComponent.hpp
)

find_package(SDL3 CONFIG REQUIRED)

if(TARGET SDL3::SDL3-shared)
    set(SDL3_TARGET SDL3::SDL3-shared)
else()
    set(SDL3_TARGET SDL3::SDL3)
endif()

target_include_directories(${PIXEL_PAD_INFRASTRUCTURE_TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PIXEL_PAD_INFRASTRUCTURE_TARGET_NAME}
    PRIVATE  
        ${SDL3_TARGET}
        ${PIXEL_PAD_CORE_TARGET_NAME}
        ${PIXEL_PAD_APPLICATION_TARGET_NAME}
)
