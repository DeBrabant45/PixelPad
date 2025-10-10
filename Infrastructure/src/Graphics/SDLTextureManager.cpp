#include "Graphics/SDLTextureManager.hpp"
#include "Graphics/SDLTexture.hpp"
#include <filesystem>
#include <iostream>

namespace PixelPad::Infrastructure
{
	SDLTextureManager::SDLTextureManager(SDLRenderer& renderer, const IPathProvider& pathProvider) :
		m_renderer(renderer),
		m_cache(),
		m_defaultTexture(nullptr),
		m_pathProvider(pathProvider)
	{
		m_defaultTexture = LoadDefaultTexture();
	}

	std::shared_ptr<PixelPad::Application::ITexture> SDLTextureManager::LoadTexture(const std::string& path)
	{
		auto assetPath = m_pathProvider.GetAssetsPath() / path;
		std::string assetPathStr = assetPath.string();

		if (assetPath.empty() || !std::filesystem::exists(assetPath))
		{
			std::cerr << "Warning: Asset not found: " << path << ". Using default texture." << std::endl;
			return m_defaultTexture;
		}

		auto it = m_cache.find(assetPathStr);
		if (it != m_cache.end())
		{
			if (auto existingTexture = it->second.lock())
				return existingTexture;
		}

		auto newTexture = m_renderer.CreateSDLTexture(assetPathStr);
		if (!newTexture)
		{
			std::cerr << "Warning: Failed to load texture: " << path << ". Using default texture." << std::endl;
			return m_defaultTexture;
		}

		auto sharedTexture = std::make_shared<SDLTexture>(newTexture, newTexture->w, newTexture->h);
		m_cache[assetPathStr] = sharedTexture;

		return sharedTexture;
	}

	std::shared_ptr<PixelPad::Application::ITexture> SDLTextureManager::LoadDefaultTexture()
	{
		auto assetPath = m_pathProvider.GetAssetsPath() / m_missingTextureKey;
		std::string assetPathStr = assetPath.string();

		if (!std::filesystem::exists(assetPath))
		{
			std::cerr << "Warning: Missing asset file not found: " << assetPathStr << std::endl;
			const int DEFAULT_SIZE = 32;
			SDL_Texture* pinkBoxTexture = m_renderer.CreateDefaultTexture(DEFAULT_SIZE, DEFAULT_SIZE);
			return std::make_shared<SDLTexture>(pinkBoxTexture, pinkBoxTexture->w, pinkBoxTexture->h);
		}

		auto defaultTexture = m_renderer.CreateSDLTexture(assetPathStr);
		return std::make_shared<SDLTexture>(defaultTexture, defaultTexture->w, defaultTexture->h);
	}
}