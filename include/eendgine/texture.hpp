#pragma once
#include <string>

namespace Eendgine
{
    struct Texture {
        uint id = 0;
        int width = 0;
        int height = 0;
        std::string type;
    }; 

    Texture loadTexture(std::string filePath);
}
