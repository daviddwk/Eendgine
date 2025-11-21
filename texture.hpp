#pragma once
#include <GLES3/gl3.h>
#include <filesystem>

namespace Eendgine {
struct Texture {
        GLuint id = 0;
        int width = 0;
        int height = 0;
};
struct Strip {
        Texture texture;
        size_t len;
};

Texture loadTexture(std::filesystem::path filePath);
} // namespace Eendgine
