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
        Statue(const Statue&) = delete;
        Statue& operator=(const Statue&) = delete;
        Statue(Statue&& other) {
            _VAO = other._VAO;
            _VBO = other._VBO;
            _EBO = other._EBO;
            _numIndices = other._numIndices;

            _position = other._position;
            _scale = other._scale;
            _rotation = other._rotation;
            _textureIdx = other._textureIdx;
            _textures.swap(other._textures);
        }
        Statue& operator=(Statue&& other) {
            _VAO = other._VAO;
            _VBO = other._VBO;
            _EBO = other._EBO;
            _numIndices = other._numIndices;

            _position = other._position;
            _scale = other._scale;
            _rotation = other._rotation;
            _textureIdx = other._textureIdx;
            _textures.swap(other._textures);
            return *this;
        }

        void eraseBuffers();

        void setPosition(Point position) { _position = position; };
        void setScale(Scale scale) { _scale = scale; };
        void setRotation(float x, float y, float z) {
            _rotation = Rotation(glm::radians(x), glm::radians(y), glm::radians(z));
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
        unsigned int _numIndices;
        Point _position;
        Scale _scale;
        Rotation _rotation;
        unsigned int _textureIdx;
        std::vector<Texture> _textures;
};
} // namespace Eendgine
