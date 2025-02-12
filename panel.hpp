#pragma once
#include "camera.hpp"
#include "texture.hpp"
#include "types.hpp"
#include "vertex.hpp"
#include <filesystem>
#include <map>
#include <vector>

namespace Eendgine {
// TODO combine these into one again
class Panel {
    public:
        Panel(std::filesystem::path path);
        ~Panel();
        void eraseBuffers();
        std::vector<Texture>::size_type getNumTextures();
        void setTexture(std::string texture) { _currentTexture = texture; };
        void cropTexture(Point2D upperLeft, Point2D lowerRight);
        void setPosition(Point position) {
            _position = Point{position.x, -position.y, position.z};
        };
        void setScale(Scale2D scale) { _size = Scale(scale.x, scale.y, 1.0f); };
        void setRotation(float r) { _rotation = r; };

        std::string getTextureName() { return _currentTexture; };
        Point getPosition() { return _position; };
        Scale getSize() { return _size; };
        float getRotation() { return _rotation; };
        Texture getTexture() { return _textures[_currentTexture]; };

        void draw(uint shaderId, Camera2D& camera);

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
