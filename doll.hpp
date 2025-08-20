#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include "camera.hpp"
#include "texture.hpp"
#include "types.hpp"

namespace Eendgine {
class Doll {
    public:
        Doll(std::filesystem::path dollPath);
        ~Doll();

        Doll(const Doll&) = delete;
        Doll& operator=(const Doll&) = delete;
        Doll(Doll&& other) {
            m_animation = other.m_animation;
            m_VAOs.swap(other.m_VAOs);
            m_VBOs.swap(other.m_VBOs);
            m_EBOs.swap(other.m_EBOs);
            m_numIndices = other.m_numIndices;

            m_position = other.m_position;
            m_scale = other.m_scale;
            m_rotation = other.m_rotation;
            m_animScale = other.m_animScale;
            m_textureIdx = other.m_textureIdx;
            m_textures.swap(other.m_textures);
        }
        Doll& operator=(Doll&& other) {
            m_animation = other.m_animation;
            m_VAOs.swap(other.m_VAOs);
            m_VBOs.swap(other.m_VBOs);
            m_EBOs.swap(other.m_EBOs);
            m_numIndices = other.m_numIndices;

            m_position = other.m_position;
            m_scale = other.m_scale;
            m_rotation = other.m_rotation;
            m_animScale = other.m_animScale;
            m_textureIdx = other.m_textureIdx;
            m_textures.swap(other.m_textures);
            return *this;
        }

        void eraseBuffers();

        void setAnimation(std::string animation) { m_animation = animation; }

        void setPosition(Point position) { m_position = position; };
        void setScale(Scale scale) { m_scale = scale; };
        void setRotation(float x, float y, float z) {
            m_rotation = Rotation(glm::radians(x), glm::radians(y), glm::radians(z));
        };

        void setTextureIdx(unsigned int idx) { m_textureIdx = (idx < m_textures.size() ? idx : 0); };

        std::string getAnimation() { return m_animation; };
        Point getPosition() { return m_position; };
        Scale getScale() { return m_scale; };
        Rotation getRotation() { return m_rotation; };

        Texture getTexture() { return m_textures[m_textureIdx]; };
        unsigned int getTextureIdx() { return m_textureIdx; };
        float getAnim() { return m_animScale; };

        void draw(uint shaderId, Camera3D& camera);

        void setAnim(float scale) { m_animScale = scale - (int)scale; };

    private:
        std::string m_animation;
        std::map<std::string, std::vector<unsigned int>> m_VAOs, m_VBOs, m_EBOs;
        unsigned int m_numIndices;

        Point m_position;
        Scale m_scale;
        Rotation m_rotation;
        float m_animScale;
        unsigned int m_textureIdx;
        std::vector<Texture> m_textures;
};
} // namespace Eendgine
