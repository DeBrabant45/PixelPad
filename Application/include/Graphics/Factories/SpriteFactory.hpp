#pragma once

#include "Graphics/Factories/ISpriteFactory.hpp"
#include "Graphics/ITextureManager.hpp"

namespace PixelPad::Application
{
	class SpriteFactory : public ISpriteFactory
	{
	public:
		SpriteFactory(ITextureManager& textureManager);
		std::unique_ptr<ISprite> CreateSprite(
			const std::string& path, 
			const PixelPad::Core::Transform& transform) override;

		std::unique_ptr<ISprite> CreateSprite(
			const PixelPad::Core::Color& color,
			const PixelPad::Core::Transform& transform) override;

		std::unique_ptr<IButtonSprite> CreateButtonSprite(
			const PixelPad::Core::Color& color, 
			const PixelPad::Core::Transform& transform) override;

		std::unique_ptr<IButtonSprite> CreateButtonSprite(
			const std::string& unclickedPath, 
			const std::string& clickedPath, 
			const PixelPad::Core::Transform& transform) override;

	private:
		ITextureManager& m_textureManager;
	};
}