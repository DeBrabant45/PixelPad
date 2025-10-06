#include "Graphics/SDLTextureManager.hpp"
#include "Graphics/SDLTexture.hpp"
#include <iostream>
#include <filesystem>

namespace PixelPad::Infrastructure
{
	SDLTextureManager::SDLTextureManager(SDLRenderer& renderer) :
		m_renderer(renderer)
	{

	}

	std::shared_ptr<PixelPad::Application::ITexture> PixelPad::Infrastructure::SDLTextureManager::LoadTexture(const std::string& path) 
	{ 
		auto it = m_cache.find(path);
		if (it != m_cache.end())
		{
			if (auto existingTexture = it->second.lock())
			{
				return existingTexture;
			}
		}

		auto newTexture = m_renderer.CreateSDLTexture(path);
		if (!newTexture)
			return nullptr;
		
		auto sharedTexture = std::make_shared<SDLTexture>(newTexture, newTexture->w, newTexture->h); 
		m_cache[path] = sharedTexture;

		return sharedTexture;
	}
}