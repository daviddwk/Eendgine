#pragma once
#include <filesystem>

namespace Eendgine {
struct Texture {
        uint id = 0;
        int width = 0;
        int height = 0;
};
struct Strip {
        Texture texture;
        size_t len;
};

Texture loadTexture(std::filesystem::path filePath);
} // namespace Eendgine
