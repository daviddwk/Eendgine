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
        Panel(const Panel&) = delete;
        Panel& operator=(const Panel&) = delete;
        Panel(Panel&& other) {
            _VAO = other._VAO;
            _VBO = other._VBO;
            _EBO = other._EBO;

            _position = other._position;
            _scale = other._scale;
            _rotation = other._rotation;
            _currentTexture = other._currentTexture;
            _textures.swap(other._textures);
        }
        Panel& operator=(Panel&& other) {
            _VAO = other._VAO;
            _VBO = other._VBO;
            _EBO = other._EBO;

            _position = other._position;
            _scale = other._scale;
            _rotation = other._rotation;
            _currentTexture = other._currentTexture;
            _textures.swap(other._textures);
            return *this;
        }

        enum MouseStatus {
            none,
            hover,
            click,
        };

        void setTexture(std::string texture);
        void setPosition(Point position);
        void setScale(Scale2D scale);
        void setRotation(float r);

        std::string getTextureName();
        Point getPosition();
        Scale getSize();
        float getRotation();
        Texture getTexture();

        void cropTexture(Point2D upperLeft, Point2D lowerRight);

        void eraseBuffers();
        MouseStatus isClicked(int mouseX, int mouseY, bool click);

        void draw(uint shaderId, Camera2D& camera);

    private:
        void setup(std::vector<std::filesystem::path>& texturePaths);
        Point _position;
        Scale _scale;
        float _rotation;
        unsigned int _VAO, _VBO, _EBO;
        std::string _currentTexture;
        std::map<std::string, Texture> _textures;
};
} // namespace Eendgine
