#include "PixelPadApplication.hpp"
#include <iostream>

int main()
{
    try
    {
        PixelPad::Presentation::PixelPadApplication entryPoint;
        entryPoint.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Application failed: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}