#pragma once
#include <string>

namespace Eendgine
{
    struct Texture {
        uint id;
        int width;
        int height;
    }; 

    Texture loadTexture(std::string filePath);
}
