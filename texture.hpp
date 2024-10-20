#pragma once
#include <filesystem>
#include <string>

namespace Eendgine {
struct Texture {
        uint id = 0;
        int width = 0;
        int height = 0;
};

Texture loadTexture(std::filesystem::path filePath);
} // namespace Eendgine
