#pragma once
#include "camera.hpp"
#include "texture.hpp"
#include "types.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <string>
#include <vector>

namespace Eendgine {
class Statue {
    public:
        Statue(std::string modelPath);
        ~Statue();
        Statue(const Statue&) = delete;
        Statue& operator=(const Statue&) = delete;
        Statue(Statue&& other) {
            m_VAO = other.m_VAO;
            m_VBO = other.m_VBO;
            m_EBO = other.m_EBO;
            m_numIndices = other.m_numIndices;

            m_position = other.m_position;
            m_scale = other.m_scale;
            m_rotation = other.m_rotation;
            m_textureIdx = other.m_textureIdx;
            m_textures.swap(other.m_textures);
        }
        Statue& operator=(Statue&& other) {
            m_VAO = other.m_VAO;
            m_VBO = other.m_VBO;
            m_EBO = other.m_EBO;
            m_numIndices = other.m_numIndices;

            m_position = other.m_position;
            m_scale = other.m_scale;
            m_rotation = other.m_rotation;
            m_textureIdx = other.m_textureIdx;
            m_textures.swap(other.m_textures);
            return *this;
        }

        void eraseBuffers();

        void setPosition(Point position) { m_position = position; };
        void setScale(Scale scale) { m_scale = scale; };
        void setRotation(float x, float y, float z) {
            m_rotation = Rotation(glm::radians(x), glm::radians(y), glm::radians(z));
        };

        void setTextureIdx(unsigned int idx) { m_textureIdx = (idx < m_textures.size() ? idx : 0); };

        Point getPosition() { return m_position; };
        Scale getScale() { return m_scale; };
        Rotation getRotation() { return m_rotation; };

        Texture getTexture() { return m_textures[m_textureIdx]; };
        unsigned int getTextureIdx() { return m_textureIdx; };

        void draw(uint shaderId, Camera3D& camera);

    private:
        unsigned int m_VAO, m_VBO, m_EBO;
        unsigned int m_numIndices;
        Point m_position;
        Scale m_scale;
        Rotation m_rotation;
        unsigned int m_textureIdx;
        std::vector<Texture> m_textures;
};
} // namespace Eendgine
