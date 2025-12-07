#pragma once
#include <memory>
#include <string>

namespace PixelPad::Core
{
	class Transform;
	struct Color;
}

namespace PixelPad::Application
{
	class ISprite;
	class IButtonSprite;

	class ISpriteFactory
	{
	public:
		virtual ~ISpriteFactory() = default;

		virtual std::unique_ptr<ISprite> CreateSprite(
			const std::string& path,
			const PixelPad::Core::Transform& transform) = 0;

		virtual std::unique_ptr<IButtonSprite> CreateButtonSprite(
			const PixelPad::Core::Color& color,
			const PixelPad::Core::Transform& transform) = 0;

		virtual std::unique_ptr<IButtonSprite> CreateButtonSprite(
			const std::string& unclickedPath,
			const std::string& clickedPath,
			const PixelPad::Core::Transform& transform) = 0;
	};
}