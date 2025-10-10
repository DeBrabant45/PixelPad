#pragma once

#include <memory>
#include <string>

namespace PixelPad::Application
{
	class ITexture;

	class ITextureManager
	{
	public:
		virtual ~ITextureManager() = default;
		virtual std::shared_ptr<ITexture> LoadTexture(const std::string& path) = 0;
	};
}