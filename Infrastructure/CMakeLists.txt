# Infrastructure Layer

add_library(${PIXEL_PAD_INFRASTRUCTURE_TARGET_NAME}
    include/Renderers/IRenderer.hpp

    src/Renderers/SDLRenderer.cpp
    include/Renderers/SDLRenderer.hpp

    include/Windows/IWindow.hpp

    src/Windows/SDLWindow.cpp
    include/Windows/SDLWindow.hpp
)

find_package(SDL3 CONFIG REQUIRED)

target_include_directories(${PIXEL_PAD_INFRASTRUCTURE_TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PIXEL_PAD_INFRASTRUCTURE_TARGET_NAME}
    PUBLIC 
        SDL3::SDL3-shared
        ${PIXEL_PAD_CORE_TARGET_NAME}
)
