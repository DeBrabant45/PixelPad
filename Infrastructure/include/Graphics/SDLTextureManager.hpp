#pragma once

#include "Graphics/ITextureManager.hpp"
#include "Graphics/ITexture.hpp"
#include "Renderers/SDLRenderer.hpp"
#include "Paths/IPathProvider.hpp"

#include <unordered_map>
#include <string>

namespace PixelPad::Infrastructure
{
	class SDLTextureManager : public PixelPad::Application::ITextureManager
	{
	public:
		SDLTextureManager(SDLRenderer& renderer, const IPathProvider& pathProvider);
		std::shared_ptr<PixelPad::Application::ITexture> LoadTexture(const std::string& path) override;

	private:
		std::shared_ptr<PixelPad::Application::ITexture> LoadDefaultTexture();

	private:
		SDLRenderer& m_renderer;
		std::unordered_map<std::string, std::weak_ptr<PixelPad::Application::ITexture>> m_cache;
		std::shared_ptr<PixelPad::Application::ITexture> m_defaultTexture;
		const IPathProvider& m_pathProvider;
		const std::string m_missingTextureKey = "--missing--.bmp";
	};
}