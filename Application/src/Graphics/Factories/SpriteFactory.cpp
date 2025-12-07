#include "Graphics/Factories/SpriteFactory.hpp"
#include "Graphics/ISprite.hpp"
#include "Graphics/IButtonSprite.hpp"
#include "Graphics/ButtonSprite.hpp"
#include "Graphics/Color.hpp"

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
		const PixelPad::Core::Color& color, 
		const PixelPad::Core::Transform& transform)
	{
		auto buttonSpriteTexture = PixelPad::Application::ButtonSpriteTexture
		{
			m_textureManager.LoadTexture(color),
			m_textureManager.LoadTexture(color),
		};
		return std::make_unique<ButtonSprite>(transform, buttonSpriteTexture);
	}

	std::unique_ptr<IButtonSprite> SpriteFactory::CreateButtonSprite(
		const std::string& unclickedPath, 
		const std::string& clickedPath, 
		const PixelPad::Core::Transform& transform)
	{
		auto buttonSpriteTexture = PixelPad::Application::ButtonSpriteTexture
		{
			m_textureManager.LoadTexture(unclickedPath),
			m_textureManager.LoadTexture(clickedPath),
		};
		return std::make_unique<ButtonSprite>(transform, buttonSpriteTexture);
	}
}