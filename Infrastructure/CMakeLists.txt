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

    src/Graphics/UIButton.cpp
    include/Graphics/UIButton.hpp

    src/Graphics/UIRoot.cpp
    include/Graphics/UIRoot.hpp

    src/Graphics/UIToolsPanel.cpp
    include/Graphics/UIToolsPanel.hpp

    src/Graphics/SDLTextureManager.cpp
    include/Graphics/SDLTextureManager.hpp

    include/Paths/IPathProvider.hpp
    include/Paths/AssetPathProvider.hpp
    src/Paths/AssetPathProvider.cpp
)

find_package(SDL3 CONFIG REQUIRED)

target_include_directories(${PIXEL_PAD_INFRASTRUCTURE_TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PIXEL_PAD_INFRASTRUCTURE_TARGET_NAME}
    PRIVATE  
        SDL3::SDL3-shared
        ${PIXEL_PAD_CORE_TARGET_NAME}
        ${PIXEL_PAD_APPLICATION_TARGET_NAME}
)
