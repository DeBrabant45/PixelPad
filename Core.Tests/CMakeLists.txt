# Core.Tests Layer

add_executable(${PIXEL_PAD_CORE_TESTS_TARGET_NAME}
    Graphics/CanvasTests.cpp
    Graphics/CanvasSnapshotTests.cpp

    Tools/PencilToolTests.cpp
    Tools/LineToolTests.cpp
    Tools/EraserToolTests.cpp
    Tools/FillToolTests.cpp
    Tools/RectangleToolTests.cpp
    Tools/EllipseToolTests.cpp

    Graphics/ColorTests.cpp
)

target_include_directories(${PIXEL_PAD_CORE_TESTS_TARGET_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/Core/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Use vcpkg-managed GTest without hardcoded path
find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PIXEL_PAD_CORE_TESTS_TARGET_NAME}
    PRIVATE
        ${PIXEL_PAD_CORE_TARGET_NAME}
        GTest::gtest
        GTest::gtest_main
)

# Register tests
add_test(NAME PixelPad.Core.Tests COMMAND ${PIXEL_PAD_CORE_TESTS_TARGET_NAME})

set_target_properties(${PIXEL_PAD_CORE_TESTS_TARGET_NAME} PROPERTIES FOLDER "PixelPad.Tests")