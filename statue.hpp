#pragma once

#include <string>
#include <vector>

#include <GLES3/gl3.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "camera.hpp"
#include "texture.hpp"
#include "types.hpp"
#include "vertex.hpp"

namespace Eendgine {
class Statue {
    public:
        Statue(std::string modelPath);
        ~Statue();
        Statue(const Statue&) = delete;
        Statue& operator=(const Statue&) = delete;
        Statue(Statue&& other) {
            position = other.position;
            scale = other.scale;
            rotation = other.rotation;

            VAO = other.VAO;
            VBO = other.VBO;
            EBO = other.EBO;
            numIndices = other.numIndices;

            textureIdx = other.textureIdx;
            textures.swap(other.textures);
        }
        Statue& operator=(Statue&& other) {
            position = other.position;
            scale = other.scale;
            rotation = other.rotation;

            VAO = other.VAO;
            VBO = other.VBO;
            EBO = other.EBO;
            numIndices = other.numIndices;

            textureIdx = other.textureIdx;
            textures.swap(other.textures);
            return *this;
        }

        void eraseBuffers();

        void setTextureIdx(unsigned int idx) { textureIdx = (idx < textures.size() ? idx : 0); };

        Texture getTexture() { return textures[textureIdx]; };
        unsigned int getTextureIdx() { return textureIdx; };

        void draw(uint shaderId, Camera3D& camera);

        Point position;
        Scale scale;
        Rotation rotation;

    private:
        GLuint VAO, VBO, EBO;
        unsigned int numIndices;
        unsigned int textureIdx;
        std::vector<Texture> textures;
};
} // namespace Eendgine
