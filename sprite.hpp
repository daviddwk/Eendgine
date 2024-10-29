#pragma once
#include "camera.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "types.hpp"
#include "vertex.hpp"
#include <filesystem>
#include <vector>

namespace Eendgine {
// TODO combine these into one again
class Sprite {
    public:
        Sprite(std::filesystem::path texturePath);
        Sprite(std::vector<std::filesystem::path> texturePaths);
        std::vector<Texture>::size_type getNumTextures();
        void setTextureIdx(std::vector<Texture>::size_type textureIdx) {
            _textureIdx = (textureIdx < _textures.size()) ? textureIdx : 0;
        };
        void setPosition(Point position) { _position = position; };
        void setScale(float w, float h) { _size = Scale(w, h, 1.0f); };
        void setRotation(float r) { _rotation = r; };

        unsigned int getTextureIdx() { return _textureIdx; };
        Point getPosition() { return _position; };
        Scale getSize() { return _size; };
        float getRotation() { return _rotation; };
        Texture getTexture() { return _textures[_textureIdx]; };

        void draw(uint shaderId, Camera2D& camera);
        void draw(uint shaderId, Camera3D& camera);

    private:
        void setup(std::vector<std::filesystem::path>& texturePaths);
        Point _position;
        Scale _size;
        float _rotation;
        unsigned int _VAO;
        unsigned int _textureIdx;
        std::vector<Texture> _textures;
};
} // namespace Eendgine
