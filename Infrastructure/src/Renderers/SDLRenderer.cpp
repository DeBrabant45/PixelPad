#include "Renderers/SDLRenderer.hpp"
#include "Windows/IWindow.hpp"
#include "Graphics/Canvas.hpp"
#include "Graphics/ITexture.hpp"
#include "Graphics/SDLTexture.hpp"
#include "Graphics/CanvasViewport.hpp"
#include "Graphics/ISprite.hpp"
#include "Graphics/Color.hpp"

#include <iostream>
#include <SDL3/SDL.h>

namespace PixelPad::Infrastructure
{
    SDLRenderer::SDLRenderer(PixelPad::Application::IWindow& window) :
        m_window(window),
		m_sdlRenderer(nullptr),
		m_canvasTexture(nullptr),
		m_canvasWidth(0),
		m_canvasHeight(0)
    {
        CreateRenderer();
    }

    void SDLRenderer::CreateRenderer()
    {
        SDL_Window* sdlWindow = static_cast<SDL_Window*>(m_window.GetNativeWindow());
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

    SDLRenderer::~SDLRenderer()
    {
		Shutdown();
    }

    void SDLRenderer::Shutdown()
    {
        if (m_sdlRenderer)
        {
            SDL_DestroyRenderer(m_sdlRenderer);
            m_sdlRenderer = nullptr;
        }

        if (m_canvasTexture)
        {
            SDL_DestroyTexture(m_canvasTexture);
            m_canvasTexture = nullptr;
        }
    }

    void SDLRenderer::ClearScreen()
    {
        if (!m_sdlRenderer)
        {
            std::cerr << "SDL Renderer is null and cannot clear screen!" << std::endl;
            return;
        }

        SDL_SetRenderDrawColor(m_sdlRenderer, 192, 192, 192, 255);
        SDL_RenderClear(m_sdlRenderer);
    }

    void SDLRenderer::Render(const PixelPad::Core::Canvas& canvas, PixelPad::Application::CanvasViewport& canvasViewport)
    {
        int width = canvas.GetWidth();
        int height = canvas.GetHeight();
        const std::vector<int>& pixels = canvas.GetPixels();

        CreateCanvasTexture(width, height);
        if (!m_canvasTexture)
            return;

        if (!UpdateTextures(pixels, width, height))
            return;

        SDL_FRect dstRect = {
            static_cast<float>(canvasViewport.GetXOffset()),
            static_cast<float>(canvasViewport.GetYOffset()),
            static_cast<float>(width),
            static_cast<float>(height)
        };

        SDL_RenderTexture(m_sdlRenderer, m_canvasTexture, nullptr, &dstRect);
    }

    void SDLRenderer::Render(PixelPad::Application::ISprite* sprite)
    {
        auto* texture = static_cast<const SDLTexture*>(sprite->GetTexture().get());
        if (!texture)
            return;

        SDL_Texture* nativeTex = texture->GetSDLTexture();
        if (!nativeTex)
            return;

        SDL_FRect dstRect{
            static_cast<float>(sprite->GetXCoordinate()),
            static_cast<float>(sprite->GetYCoordinate()),
            static_cast<float>(sprite->GetWidth()),
            static_cast<float>(sprite->GetHeight())
        };

        if (SDL_RenderTexture(m_sdlRenderer, nativeTex, nullptr, &dstRect) == 0)
        {
            std::cerr << "Failed to render texture: " << SDL_GetError() << std::endl;
        }
    }

    void SDLRenderer::CreateCanvasTexture(int width, int height)
    {
        if (m_canvasTexture && (m_canvasWidth == width && m_canvasHeight == height))
            return;

        if (m_canvasTexture)
            SDL_DestroyTexture(m_canvasTexture);

        m_canvasTexture = SDL_CreateTexture(
            m_sdlRenderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            width,
            height
        );

        if (!m_canvasTexture)
        {
            std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
            return;
        }

        m_canvasWidth = width;
        m_canvasHeight = height;
    }

    bool SDLRenderer::UpdateTextures(const std::vector<int>& pixels, int width, int height)
    {
        void* texturePixels = nullptr;
        int pitch = 0;

        if (!SDL_LockTexture(m_canvasTexture, nullptr, &texturePixels, &pitch))
        {
            std::cerr << "Failed to lock texture: " << SDL_GetError() << std::endl;
            return false;
        }

        for (int y = 0; y < height; ++y)
        {
            std::memcpy(
                static_cast<uint8_t*>(texturePixels) + y * pitch,
                &pixels[y * width],
                width * sizeof(int)
            );
        }

        SDL_UnlockTexture(m_canvasTexture);
        return true;
    }

    void SDLRenderer::Present()
    {
        if (!m_sdlRenderer)
        {
            std::cerr << "SDL Renderer is null and cannot present to screen!" << std::endl;
            return;
        }

        SDL_RenderPresent(m_sdlRenderer);
    }

    SDL_Texture* SDLRenderer::CreateSDLTexture(const std::string& filePath)
    {
        SDL_Texture* sdlTexture = nullptr;
        SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
        if (!surface)
        {
            std::cerr << "Failed to load texture: " << SDL_GetError() << "\n";
            return nullptr;
        }

        sdlTexture = SDL_CreateTextureFromSurface(m_sdlRenderer, surface);
        SDL_DestroySurface(surface);

        if (!sdlTexture)
        {
            std::cerr << "Failed to create SDL texture: " << SDL_GetError() << "\n";
            return nullptr;
        }

        return sdlTexture;
    }

    SDL_Texture* SDLRenderer::CreateSDLTexture(int width, int height, const PixelPad::Core::Color& color)
    {
        SDL_Texture* texture = SDL_CreateTexture(
            m_sdlRenderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            width, height
        );

        if (!texture) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create default texture: %s", SDL_GetError());
            return nullptr;
        }

        SDL_Texture* oldTarget = SDL_GetRenderTarget(m_sdlRenderer);
        SDL_SetRenderTarget(m_sdlRenderer, texture);

        SDL_SetRenderDrawColor(m_sdlRenderer, color.R, color.G, color.B, color.A);
        SDL_RenderClear(m_sdlRenderer);

        SDL_SetRenderTarget(m_sdlRenderer, oldTarget);

        return texture;
    }
}