#include "EntryPoint.hpp"
#include <iostream>

namespace Entry
{
	EntryPoint::EntryPoint() : 
		m_canvasModel{ 800, 600 },
		m_renderer()
	{

	}

	EntryPoint::~EntryPoint()
	{

	}

    void EntryPoint::Initialize()
    {
        std::cout << "Initializing PixelPad..." << std::endl;
    }

    void EntryPoint::Shutdown()
    {
        std::cout << "Shutting down PixelPad..." << std::endl;
    }

    void EntryPoint::Run()
    {
        Initialize();

        try
        {
            std::cout << "PixelPad launched successfully!" << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            Shutdown();
        }

        Shutdown();
    }
}