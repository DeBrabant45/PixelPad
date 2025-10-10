#include "gtest/gtest.h"
#include "Paths/AssetPathProvider.hpp"
#include <filesystem>

namespace PixelPad::Tests::Infrastructure
{
    namespace fs = std::filesystem;

    TEST(AssetPathProviderTests, GetAssetsPath_ShouldReturnAssets_WhenInCurrentDirectory)
    {
        auto oldCwd = fs::current_path();
        auto tempDir = fs::temp_directory_path() / "PixelPadTestCurrent";
        fs::create_directories(tempDir / "Assets");
        fs::current_path(tempDir);

        PixelPad::Infrastructure::AssetPathProvider sut;
        auto result = sut.GetAssetsPath();

        EXPECT_EQ(result, tempDir / "Assets");

        fs::current_path(oldCwd);
        fs::remove_all(tempDir);
    }

    TEST(AssetPathProviderTests, GetAssetsPath_ShouldReturnAssets_WhenInParentDirectory)
    {
        auto oldCwd = fs::current_path();
        auto tempDir = fs::temp_directory_path() / "PixelPadTestParent";
        fs::create_directories(tempDir / "Assets");
        fs::path childDir = tempDir / "child";
        fs::create_directories(childDir);
        fs::current_path(childDir);

        PixelPad::Infrastructure::AssetPathProvider sut;
        auto result = sut.GetAssetsPath();

        EXPECT_EQ(result, tempDir / "Assets");

        fs::current_path(oldCwd);
        fs::remove_all(tempDir);
    }

    TEST(AssetPathProviderTests, GetAssetsPath_ShouldReturnEmpty_WhenAssetsAreNotFound)
    {
        auto oldCwd = fs::current_path();
        auto tempDir = fs::temp_directory_path() / "PixelPadTestEmpty";
        fs::create_directories(tempDir);
        fs::current_path(tempDir);

        PixelPad::Infrastructure::AssetPathProvider sut;
        auto result = sut.GetAssetsPath();

        EXPECT_TRUE(result.empty());

        fs::current_path(oldCwd);
        fs::remove_all(tempDir);
    }
}