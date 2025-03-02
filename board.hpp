#pragma once
#include <filesystem>
#include <map>
#include <vector>

#include <GLES3/gl3.h>

#include "camera.hpp"
#include "texture.hpp"
#include "types.hpp"
#include "vertex.hpp"

namespace Eendgine {
class Board {
    public:
        Board(std::filesystem::path path);
        ~Board();
        Board(const Board&) = delete;
        Board& operator=(const Board&) = delete;
        Board(Board&& other) {
            position = other.position;
            scale = other.scale;
            rotation = other.rotation;

            VAO = other.VAO;
            VBO = other.VBO;
            EBO = other.EBO;

            currentTextureIdx = other.currentTextureIdx;
            textures.swap(other.textures);
            textureMap.swap(other.textureMap);
        }
        Board& operator=(Board&& other) {
            position = other.position;
            scale = other.scale;
            rotation = other.rotation;

            VAO = other.VAO;
            VBO = other.VBO;
            EBO = other.EBO;

            currentTextureIdx = other.currentTextureIdx;
            textures.swap(other.textures);
            textureMap.swap(other.textureMap);
            return *this;
        }
        void eraseBuffers();
        std::vector<Texture>::size_type getNumTextures();
        void setTexture(std::string textureName);
        void setTextureIdx(size_t textureIdx) { currentTextureIdx = textureIdx % textures.size(); };

        Texture getTexture() { return textures[currentTextureIdx]; };

        void draw(uint shaderId, Camera3D& camera);

        Point position;
        Scale2D scale;
        float rotation;

    private:
        void setup(std::vector<std::filesystem::path>& texturePaths);
        GLuint VAO, VBO, EBO;
        size_t currentTextureIdx;
        std::map<std::string, size_t> textureMap;
        std::vector<Texture> textures;
};
} // namespace Eendgine
