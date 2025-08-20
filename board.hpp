#pragma once
#include "camera.hpp"
#include "texture.hpp"
#include "types.hpp"
#include "vertex.hpp"
#include <filesystem>
#include <map>
#include <vector>

namespace Eendgine {
class Board {
    public:
        Board(std::filesystem::path path);
        ~Board();

        void eraseBuffers();

        void setStrip(std::string strip);
        void setStripIdx(size_t idx);
        void nextStripIdx();
        void setFlip(bool flip);

        void setPosition(Point position);
        void setScale(Scale2D scale);
        void setRotation(float r);

        size_t getStripLen();
        size_t getStripIdx();

        Point getPosition();
        Scale getSize();
        float getRotation();

        Texture getTexture();

        std::vector<Texture>::size_type getNumTextures();
        void draw(uint shaderId, Camera3D& camera);

    private:
        void setup(
            std::vector<std::filesystem::path>& texturePaths, std::filesystem::path& metadataPath);

        Point m_position;
        Scale m_size;
        float m_rotation;
        unsigned int m_VAO, m_VBO, m_EBO;
        std::string m_currentStrip;
        size_t m_currentStripIdx;
        bool m_flipStrip;
        std::map<std::string, size_t> m_stripMap;
        std::vector<Strip> m_strips;
};
} // namespace Eendgine
