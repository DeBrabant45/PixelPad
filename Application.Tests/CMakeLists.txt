# Application.Tests Layer

add_executable(${PIXEL_PAD_APPLICATION_TESTS_TARGET_NAME}
    src/Services/DrawServiceTests.cpp
)

target_include_directories(${PIXEL_PAD_APPLICATION_TESTS_TARGET_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/Application/include
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PIXEL_PAD_APPLICATION_TESTS_TARGET_NAME}
    PRIVATE
        ${PIXEL_PAD_APPLICATION_TARGET_NAME}
        GTest::gtest
        GTest::gtest_main
)

add_test(NAME PixelPad.Application.Tests COMMAND ${PIXEL_PAD_APPLICATION_TESTS_TARGET_NAME})

set_target_properties(${PIXEL_PAD_APPLICATION_TESTS_TARGET_NAME} PROPERTIES FOLDER "PixelPad.Tests")