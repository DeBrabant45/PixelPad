# Presentation Layer

add_library(${PIXEL_PAD_PRESENTATION_TARGET_NAME}
    src/CanvasController.cpp
    include/CanvasController.hpp
)

target_include_directories(${PIXEL_PAD_PRESENTATION_TARGET_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PIXEL_PAD_PRESENTATION_TARGET_NAME}
    PRIVATE
        ${PIXEL_PAD_APPLICATION_TARGET_NAME}
)
