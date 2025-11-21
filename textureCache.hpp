#pragma once
#include "texture.hpp"
#include <filesystem>
#include <map>

namespace Eendgine {
class TextureCache {
    public:
        static Texture getTexture(std::filesystem::path texturePath);

    private:
        inline static std::map<std::filesystem::path, Texture> m_textureMap;
};
} // namespace Eendgine
