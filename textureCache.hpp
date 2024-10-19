#pragma once
#include "texture.hpp"
#include <filesystem>
#include <map>
#include <string>

namespace Eendgine {
class TextureCache {
  public:
    static Texture getTexture(std::filesystem::path texturePath);

  private:
    inline static std::map<std::string, Texture> _textureMap;
};
} // namespace Eendgine
