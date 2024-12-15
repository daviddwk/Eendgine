#pragma once
#include "camera.hpp"
#include "texture.hpp"
#include "types.hpp"
#include "vertex.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <string>
#include <vector>

namespace Eendgine {
class Statue {
    public:
        Statue(std::string modelPath);
        ~Statue();

        void eraseBuffers();

        void setPosition(Point position) { _position = position; };
        void setScale(Scale scale) { _scale = scale; };
        void setRadians(float x, float y) { _rotation = Rotation(x, y); };
        void setRotation(float x, float y) {
            _rotation = Rotation(glm::radians(x), glm::radians(y));
        };

        void setTextureIdx(unsigned int idx) { _textureIdx = (idx < _textures.size() ? idx : 0); };

        Point getPosition() { return _position; };
        Scale getScale() { return _scale; };
        Rotation getRotation() { return _rotation; };

        Texture getTexture() { return _textures[_textureIdx]; };
        unsigned int getTextureIdx() { return _textureIdx; };

        void draw(uint shaderId, Camera3D& camera);

    private:
        unsigned int _VAO, _VBO, _EBO;
        std::vector<Vertex> _vertices;
        std::vector<unsigned int> _indices;
        Point _position;
        Scale _scale;
        Rotation _rotation;
        unsigned int _textureIdx;
        std::vector<Texture> _textures;
        std::string _name;
};
} // namespace Eendgine
