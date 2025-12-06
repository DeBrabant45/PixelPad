#include "PixelPadApplication.hpp"
#include <iostream>
#include <exception>

int main()
{
    try
    {
        PixelPad::Presentation::PixelPadApplication entryPoint;
        entryPoint.Run();
    }
    catch (const std::bad_alloc& e)
    {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Application failed: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Application failed: unknown exception" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
