# Presentation Layer

add_executable(${PIXEL_PAD_PRESENTATION_TARGET_NAME}
    src/Controllers/CanvasController.cpp
    include/Controllers/CanvasController.hpp

    src/Controllers/WindowController.cpp
    include/Controllers/WindowController.hpp

    src/Controllers/RendererController.cpp
    include/Controllers/RendererController.hpp

    src/PixelPadApplication.cpp
    include/PixelPadApplication.hpp

    src/Main.cpp
)

target_include_directories(${PIXEL_PAD_PRESENTATION_TARGET_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PIXEL_PAD_PRESENTATION_TARGET_NAME}
   PRIVATE
        ${PIXEL_PAD_CORE_TARGET_NAME}
        ${PIXEL_PAD_APPLICATION_TARGET_NAME}
        ${PIXEL_PAD_INFRASTRUCTURE_TARGET_NAME}
)
