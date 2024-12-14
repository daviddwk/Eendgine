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

        void setAnimation(std::string animation) { _animation = animation; }

        void setPosition(Point position) { _position = position; };
        void setScale(Scale scale) { _scale = scale; };
        void setRadians(float x, float y) { _rotation = Rotation(x, y); };
        void setRotation(float x, float y) {
            _rotation = Rotation(glm::radians(x), glm::radians(y));
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
        std::map<std::string, std::vector<unsigned int>> _VAOs, _EBOs, _VBOs;
        std::map<std::string, std::vector<std::vector<InpolVertex>>> _vertices;
        std::map<std::string, std::vector<std::vector<unsigned int>>> _indices;

        Point _position;
        Scale _scale;
        Rotation _rotation;
        float _animScale;
        unsigned int _textureIdx;
        std::vector<Texture> _textures;
};
} // namespace Eendgine
