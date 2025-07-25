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

        enum MouseStatus {
            NONE,
            HOVER,
            CLICK,
        };

        void setTexture(std::string texture);
        void setPosition(Point position);
        void setScale(Scale2D scale);
        void setRotation(float r);

        std::string getTextureName();
        Point getPosition();
        Scale getScale();
        float getRotation();
        Texture getTexture();

        void cropTexture(Point2D upperLeft, Point2D lowerRight);

        void eraseBuffers();
        MouseStatus isClicked();

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
