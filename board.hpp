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
        /*
        Board(const Board&) = delete;
        Board& operator=(const Board&) = delete;
        Board(Board&& other) {
            _VAO = other._VAO;
            _VBO = other._VBO;
            _EBO = other._EBO;

            _position = other._position;
            _size = other._size;
            _rotation = other._rotation;
            _currentTextureIdx = other._currentTextureIdx;
            _textures.swap(other._textures);
            _textureMap.swap(other._textureMap);
        }
        Board& operator=(Board&& other) {
            _VAO = other._VAO;
            _VBO = other._VBO;
            _EBO = other._EBO;

            _position = other._position;
            _size = other._size;
            _rotation = other._rotation;
            _currentTextureIdx = other._currentTextureIdx;
            _textures.swap(other._textures);
            _textureMap.swap(other._textureMap);
            return *this;
        }
        */
        void eraseBuffers();
        std::vector<Texture>::size_type getNumTextures();
        void setStrip(std::string strip) { _currentStrip = strip; };
        void setStripIdx(size_t idx) { _currentStripIdx = idx; };
        void setFlip(bool flip) { _flipStrip = flip; };
        void nextStripIdx() { _currentStripIdx++; }; // TODO loop
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
