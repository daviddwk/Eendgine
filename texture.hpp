#pragma once
#include <GLES3/gl3.h>
#include <filesystem>
#include <map>

namespace Eendgine {

// TODO make a way to unload textures (at least in destructor)
// and make a singleton like everything else

struct Texture {
        GLuint id = 0;
        int width = 0;
        int height = 0;
};

class TextureCache {
    public:
        static Texture getTexture(std::filesystem::path texturePath);

    private:
        static Texture loadTexture(std::filesystem::path filePath);
        inline static std::map<std::filesystem::path, Texture> m_textureMap;
};

} // namespace Eendgine
