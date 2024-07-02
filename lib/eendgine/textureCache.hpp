#pragma once
#include "texture.hpp"
#include <map>
#include <string>
#include <filesystem>

namespace Eendgine {
    class TextureCache {
        public:
            static Texture getTexture(std::filesystem::path texturePath);
        private:
            inline static std::map<std::string, Texture> _textureMap;
    };
}
