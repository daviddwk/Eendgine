#pragma once

#include "camera.hpp"
#include "strip.hpp"
#include "texture.hpp"
#include "types.hpp"

#include <filesystem>
#include <vector>

namespace Eendgine {

class Board {
    public:
        Board(std::filesystem::path path);
        ~Board() = default;

        Board(const Board& other) = delete;
        Board& operator=(const Board& other) = delete;

        Board(Board&& other) noexcept = default;
        Board& operator=(Board&& other) noexcept = default;

        void setStrip(std::string strip);
        void setStripIdx(unsigned int idx);
        void nextStripIdx();
        void setStripFlip(bool flip);

        void setPosition(Point position);
        void setScale(Scale2D scale);
        void setRotation(float r);

        std::vector<Strip>::size_type getStripLen();
        unsigned int getStripIdx();

        Point getPosition();
        Scale getSize();
        float getRotation();

        Texture getTexture() const;

        std::vector<Texture>::size_type getNumTextures();
        void draw(GLuint shaderId, Camera3D& camera);

    private:
        void setup(
            std::vector<std::filesystem::path>& texturePaths, std::filesystem::path& metadataPath);

        Point m_position;
        Scale m_size;
        float m_rotation;

        StripHandler m_stripHandler;
};
} // namespace Eendgine
