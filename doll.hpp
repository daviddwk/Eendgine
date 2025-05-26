#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include "camera.hpp"
#include "texture.hpp"
#include "types.hpp"
#include "vertex.hpp"

namespace Eendgine {
class Doll {
    public:
        Doll(std::filesystem::path dollPath);
        ~Doll();

        Doll(const Doll&) = delete;
        Doll& operator=(const Doll&) = delete;
        Doll(Doll&& other) {
            _animation = other._animation;
            _VAOs.swap(other._VAOs);
            _VBOs.swap(other._VBOs);
            _EBOs.swap(other._EBOs);
            _numIndices = other._numIndices;

            _position = other._position;
            _scale = other._scale;
            _rotation = other._rotation;
            _animScale = other._animScale;
            _textureIdx = other._textureIdx;
            _textures.swap(other._textures);
        }
        Doll& operator=(Doll&& other) {
            _animation = other._animation;
            _VAOs.swap(other._VAOs);
            _VBOs.swap(other._VBOs);
            _EBOs.swap(other._EBOs);
            _numIndices = other._numIndices;

            _position = other._position;
            _scale = other._scale;
            _rotation = other._rotation;
            _animScale = other._animScale;
            _textureIdx = other._textureIdx;
            _textures.swap(other._textures);
            return *this;
        }

        void eraseBuffers();

        void setAnimation(std::string animation) { _animation = animation; }

        void setPosition(Point position) { _position = position; };
        void setScale(Scale scale) { _scale = scale; };
        void setRotation(float x, float y, float z) {
            _rotation = Rotation(glm::radians(x), glm::radians(y), glm::radians(z));
        };

        void setTextureIdx(unsigned int idx) { _textureIdx = (idx < _textures.size() ? idx : 0); };

        std::string getAnimation() { return _animation; };
        Point getPosition() { return _position; };
        Scale getScale() { return _scale; };
        Rotation getRotation() { return _rotation; };

        Texture getTexture() { return _textures[_textureIdx]; };
        unsigned int getTextureIdx() { return _textureIdx; };
        float getAnim() { return _animScale; };

        void draw(uint shaderId, Camera3D& camera);

        void setAnim(float scale) { _animScale = scale - (int)scale; };

    private:
        std::string _animation;
        std::map<std::string, std::vector<unsigned int>> _VAOs, _VBOs, _EBOs;
        unsigned int _numIndices;
        // std::map<std::string, std::vector<std::vector<InpolVertex>>> _vertices;
        // std::map<std::string, std::vector<std::vector<unsigned int>>> _indices;

        Point _position;
        Scale _scale;
        Rotation _rotation;
        float _animScale;
        unsigned int _textureIdx;
        std::vector<Texture> _textures;
};
} // namespace Eendgine
