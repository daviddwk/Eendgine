#pragma once

#include "camera.hpp"

#include "strip.hpp"
#include "types.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <print>
#include <string>
#include <vector>

namespace Eendgine {
class Statue {
    public:
        Statue(std::string statuePath);
        ~Statue();

        Statue(const Statue& other) = delete;
        Statue& operator=(const Statue& other) = delete;

        Statue(Statue&& other) noexcept;
        Statue& operator=(Statue&& other) noexcept;

        void setPosition(Point position) { m_position = position; };
        void setScale(Scale scale) { m_scale = scale; };
        void setRotation(Rotation rotation) {
            m_rotation = Rotation(
                glm::radians(rotation.x),
                glm::radians(rotation.y),
                glm::radians(rotation.z));
        };

        void setStrip(std::string strip) { m_stripHandler.setStrip(strip); };
        void setStripIdx(unsigned int idx) { m_stripHandler.setStripIdx(idx); };
        void setStripFlip(bool flip) { m_stripHandler.setStripFlip(flip); };
        void nextStripIdx() { m_stripHandler.nextStripIdx(); };

        Point getPosition() { return m_position; };
        Scale getScale() { return m_scale; };
        Rotation getRotation() { return m_rotation; };

        std::vector<Strip>::size_type getStripLen() { return m_stripHandler.getStripLen(); };
        unsigned int getStripIdx() { return m_stripHandler.getStripIdx(); };

        Texture getTexture() const { return m_stripHandler.getTexture(); };
        void draw(GLuint shaderId, Camera3D& camera);

    private:
        GLuint m_VAO, m_VBO, m_EBO;
        unsigned int m_numIndices;
        Point m_position;
        Scale m_scale;
        Rotation m_rotation;
        unsigned int m_textureIdx;
        StripHandler m_stripHandler;
};
} // namespace Eendgine
