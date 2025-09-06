#pragma once

#include "Graphics/ITextureManager.hpp"
#include "Graphics/ITexture.hpp"
#include "Renderers/SDLRenderer.hpp"
#include <unordered_map>

namespace PixelPad::Infrastructure
{
	class SDLTextureManager : public PixelPad::Application::ITextureManager
	{
	public:
		SDLTextureManager(SDLRenderer& renderer);
		std::shared_ptr<PixelPad::Application::ITexture> LoadTexture(const std::string& path) override;

	private:
		SDLRenderer& m_renderer;
		std::unordered_map<std::string, std::weak_ptr<PixelPad::Application::ITexture>> m_cache;
	};
}