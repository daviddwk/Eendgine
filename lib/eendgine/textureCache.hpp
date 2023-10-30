#pragma once
#include "texture.hpp"
#include <map>
#include <string>

namespace Eendgine {
    class TextureCache {
        public:
            TextureCache();
            ~TextureCache();
            
            Texture getTexture(std::string texturePath);
        private:
            std::map<std::string, Texture> _textureMap;
    };
}
