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
        Board(const Board&) = delete;
        Board& operator=(const Board&) = delete;
        Board(Board&& other) {
            _VAO = other._VAO;
            _VBO = other._VBO;
            _EBO = other._EBO;

            _position = other._position;
            _size = other._size;
            _rotation = other._rotation;
            _currentTexture = other._currentTexture;
            _textures.swap(other._textures);
        }
        Board& operator=(Board&& other) {
            _VAO = other._VAO;
            _VBO = other._VBO;
            _EBO = other._EBO;

            _position = other._position;
            _size = other._size;
            _rotation = other._rotation;
            _currentTexture = other._currentTexture;
            _textures.swap(other._textures);
            return *this;
        }
        void eraseBuffers();
        std::vector<Texture>::size_type getNumTextures();
        void setTexture(std::string texture) { _currentTexture = texture; };
        void setPosition(Point position) { _position = position; };
        void setScale(Scale2D scale) { _size = Scale(scale.x, scale.y, 1.0f); };
        void setRotation(float r) { _rotation = r; };

        std::string getTextureName() { return _currentTexture; };
        Point getPosition() { return _position; };
        Scale getSize() { return _size; };
        float getRotation() { return _rotation; };
        Texture getTexture() { return _textures[_currentTexture]; };

        void draw(uint shaderId, Camera3D& camera);

    private:
        void setup(std::vector<std::filesystem::path>& texturePaths);
        Point _position;
        Scale _size;
        float _rotation;
        unsigned int _VAO, _VBO, _EBO;
        std::string _currentTexture;
        std::map<std::string, Texture> _textures;
};
} // namespace Eendgine
