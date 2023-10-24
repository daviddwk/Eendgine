#include "textureCache.hpp"

#include <stb/stb_image.h>

namespace Eendgine
{

    TextureCache::TextureCache(){

    }

    TextureCache::~TextureCache(){

    }

    Texture TextureCache::getTexture(std::string texturePath) {
        auto mapItr = _textureMap.find(texturePath);
        if (mapItr == _textureMap.end()) {
            Texture texture = loadTexture(texturePath);
            mapItr = _textureMap.insert(std::begin(_textureMap), {texturePath, texture});
        }
        return mapItr->second;
    }

}
