#pragma once
#include "texture.hpp"
#include <map>
#include <string>

namespace Eendgine {
    class TextureCache {
        public:
            static Texture getTexture(std::string texturePath);
        private:
            inline static std::map<std::string, Texture> _textureMap;
    };
}
