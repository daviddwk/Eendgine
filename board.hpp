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
        Point _position;
        Scale _size;
        float _rotation;
        unsigned int _VAO, _VBO, _EBO;
        std::string _currentStrip;
        size_t _currentStripIdx;
        bool _flipStrip;
        std::map<std::string, size_t> _stripMap;
        std::vector<Strip> _strips;
};
} // namespace Eendgine
