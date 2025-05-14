#include "Renderer.hpp"
#include <iostream>
#include <SDL3/SDL.h>
#include "Window.hpp"
#include "Graphics/Canvas.hpp"

namespace PixelPad::Infrastructure
{
    Renderer::Renderer(IWindow& window) :
        m_window(window)
    {
        SDL_Window* sdlWindow = m_window.GetNativeWindow();
        if (!sdlWindow)
        {
            std::cerr << "SDL Window is not available." << std::endl;
            return;
        }

        m_sdlRenderer = SDL_CreateRenderer(sdlWindow, nullptr);
        if (!m_sdlRenderer)
        {
            std::cerr << "SDL Renderer Creation Error: " << SDL_GetError() << std::endl;
            return;
        }
    }

    Renderer::~Renderer()
    {
        if (m_sdlRenderer)
        {
            SDL_DestroyRenderer(m_sdlRenderer);
        }
    }

    void Renderer::ClearScreen()
    {
        if (m_sdlRenderer)
        {
            SDL_SetRenderDrawColor(m_sdlRenderer, 0, 0, 0, 255); // Clear with black color
            SDL_RenderClear(m_sdlRenderer);
        }
    }

    void Renderer::Render(const PixelPad::Core::Canvas& canvas)
    {
        int width = canvas.GetWidth();
        int height = canvas.GetHeight();
        const std::vector<int>& pixels = canvas.GetPixels();

        SDL_Texture* texture = SDL_CreateTexture(
            m_sdlRenderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            width,
            height
        );

        if (!texture)
        {
            std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
            return;
        }

        void* texturePixels = nullptr;
        int pitch = 0;

        if (!SDL_LockTexture(texture, nullptr, &texturePixels, &pitch))
        {
            std::cerr << "Failed to lock texture: " << SDL_GetError() << std::endl;
            SDL_DestroyTexture(texture);
            return;
        }

        // Copy pixel data row by row
        for (int y = 0; y < height; ++y)
        {
            std::memcpy(
                static_cast<uint8_t*>(texturePixels) + y * pitch,
                &pixels[y * width],
                width * sizeof(int)
            );
        }

        SDL_UnlockTexture(texture);

        SDL_RenderTexture(m_sdlRenderer, texture, nullptr, nullptr);

        SDL_DestroyTexture(texture);
    }

    void Renderer::Present()
    {
        if (m_sdlRenderer)
        {
            SDL_RenderPresent(m_sdlRenderer); 
        }
    }

    void Renderer::Resize(int newWidth, int newHeight)
    {
        // Optionally handle resizing logic (e.g., re-create the renderer if needed)
    }

    void Renderer::Shutdown()
    {
        if (m_sdlRenderer)
        {
            SDL_DestroyRenderer(m_sdlRenderer);
            m_sdlRenderer = nullptr;
        }
    }
}