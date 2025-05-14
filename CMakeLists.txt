cmake_minimum_required(VERSION 3.20)
project(PixelPad)

# Set the C++ standard for the project
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Target names (use throughout the project)
set(PIXEL_PAD_CORE_TARGET_NAME            PixelPad.Core)
set(PIXEL_PAD_APPLICATION_TARGET_NAME     PixelPad.Application)
set(PIXEL_PAD_PRESENTATION_TARGET_NAME    PixelPad.Presentation)
set(PIXEL_PAD_INFRASTRUCTURE_TARGET_NAME  PixelPad.Infrastructure)

set(PIXEL_PAD_CORE_TESTS_TARGET_NAME         PixelPad.Core.Tests)
set(PIXEL_PAD_APPLICATION_TESTS_TARGET_NAME  PixelPad.Application.Tests)

# Enable testing once at root
enable_testing()

# Add layers
add_subdirectory(Core)
add_subdirectory(Application)
add_subdirectory(Infrastructure)
add_subdirectory(Presentation)

# Add Test layers
add_subdirectory(Core.Tests)
add_subdirectory(Application.Tests)