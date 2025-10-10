#pragma once

#include <filesystem>

namespace PixelPad::Infrastructure
{
	class IPathProvider
	{
	public:
		virtual ~IPathProvider() = default;
		virtual std::filesystem::path GetAssetsPath() const = 0;
	};
}