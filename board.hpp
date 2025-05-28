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
        std::vector<Texture>::size_type getNumTextures();
        void setStrip(std::string strip) {
            assert(_stripMap.find(strip) != _stripMap.end());
            _currentStrip = strip;
            _currentStripIdx = 0;
        };
        void setStripIdx(size_t idx) {
            _currentStripIdx = idx % _strips[_stripMap[_currentStrip]].len;
        };
        void nextStripIdx() {
            _currentStripIdx = (_currentStripIdx + 1) % _strips[_stripMap[_currentStrip]].len;
        };
        void setFlip(bool flip) { _flipStrip = flip; };
        void setPosition(Point position) { _position = position; };
        void setScale(Scale2D scale) { _size = Scale(scale.x, scale.y, 1.0f); };
        void setRotation(float r) { _rotation = r; };

        Point getPosition() { return _position; };
        Scale getSize() { return _size; };
        float getRotation() { return _rotation; };
        Texture getTexture() { return _strips[_stripMap[_currentStrip]].texture; };
        size_t getStripLen() { return _strips[_stripMap[_currentStrip]].len; };
        size_t getStripIdx() { return _currentStripIdx; };

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
