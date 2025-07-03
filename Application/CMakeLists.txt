# Application Layer

add_library(${PIXEL_PAD_APPLICATION_TARGET_NAME}
    src/Services/DrawService.cpp
    include/Services/DrawService.hpp

    include/Services/IDrawService.hpp

    include/Enums/ToolType.hpp
    include/Enums/MouseButton.hpp

    include/Events/MouseButtonEvent.hpp
    include/Events/WindowCloseEvent.hpp
    include/Events/WindowResizeEvent.hpp
    include/Events/ToolTypeChangedEvent.hpp
)

target_include_directories(${PIXEL_PAD_APPLICATION_TARGET_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PIXEL_PAD_APPLICATION_TARGET_NAME}
    PUBLIC
        ${PIXEL_PAD_CORE_TARGET_NAME}
)
