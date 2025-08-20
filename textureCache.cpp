#include "textureCache.hpp"

#include <stb/stb_image.h>

namespace Eendgine {
Texture TextureCache::getTexture(std::filesystem::path texturePath) {
    auto mapItr = m_textureMap.find(texturePath);
    if (mapItr == m_textureMap.end()) {
        Texture texture = loadTexture(texturePath);
        mapItr = m_textureMap.insert(std::begin(m_textureMap), {texturePath, texture});
    }
    return mapItr->second;
}
} // namespace Eendgine
