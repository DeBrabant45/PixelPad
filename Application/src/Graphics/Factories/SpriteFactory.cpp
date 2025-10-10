#include "Graphics/Factories/SpriteFactory.hpp"
#include "Graphics/ISprite.hpp"
#include "Graphics/IButtonSprite.hpp"
#include "Graphics/ButtonSprite.hpp"

namespace PixelPad::Application
{
	SpriteFactory::SpriteFactory(ITextureManager& textureManager) :
		m_textureManager(textureManager)
	{

	}

	std::unique_ptr<ISprite> SpriteFactory::CreateSprite(const std::string& path, const PixelPad::Core::Transform& transform)
	{
		auto texture = m_textureManager.LoadTexture(path);
		return std::make_unique<Sprite>(transform, texture);
	}

	std::unique_ptr<IButtonSprite> SpriteFactory::CreateButtonSprite(
		const std::string& unclickedPath, 
		const std::string& clickedPath, 
		const std::string& hoverPath, 
		const PixelPad::Core::Transform& transform)
	{
		auto buttonSpriteTexture = PixelPad::Application::ButtonSpriteTexture
		{
			m_textureManager.LoadTexture(unclickedPath),
			m_textureManager.LoadTexture(clickedPath),
			m_textureManager.LoadTexture(hoverPath)
		};
		return std::make_unique<ButtonSprite>(transform, buttonSpriteTexture);
	}
}