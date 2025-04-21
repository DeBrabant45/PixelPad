# Core Layer

add_library(${PIXEL_PAD_CORE_TARGET_NAME}
    src/CanvasModel.cpp
    include/CanvasModel.hpp
)

target_include_directories(${PIXEL_PAD_CORE_TARGET_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
