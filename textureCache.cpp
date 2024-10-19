#include "textureCache.hpp"

#include <stb/stb_image.h>

namespace Eendgine {
Texture TextureCache::getTexture(std::filesystem::path texturePath) {
    auto mapItr = _textureMap.find(texturePath);
    if (mapItr == _textureMap.end()) {
        Texture texture = loadTexture(texturePath);
        mapItr = _textureMap.insert(std::begin(_textureMap), {texturePath, texture});
    }
    return mapItr->second;
}
} // namespace Eendgine
