#pragma once

#include "Paths/IPathProvider.hpp"
#include <string>

namespace PixelPad::Infrastructure
{
	class AssetPathProvider : public IPathProvider
	{
	public:
		AssetPathProvider() = default;
		std::filesystem::path GetAssetsPath() const override;

	private:
		const std::string& m_assetPathName{ "Assets" };
	};
}