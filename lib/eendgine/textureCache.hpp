#pragma once
#include <map>
#include <string>
#include "texture.hpp"

namespace Eendgine
{

    class TextureCache
    {
    public:
        TextureCache();
        ~TextureCache();
        
        Texture getTexture(std::string texturePath);
    private:
        std::map<std::string, Texture> _textureMap;
    };

}
