#include <filesystem>
#include <vector>

#include "camera.hpp"
#include "texture.hpp"
#include "types.hpp"
#include "vertex.hpp"

namespace Eendgine {
class Animation {
    public:
        Animation(std::filesystem::path modelsDir);

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
        float getAnim() { return _animScale; };

        void draw(uint shaderId, Camera3D& camera);

        void setAnim(float scale) { _animScale = scale - (int)scale; };

    private:
        float _animScale;
        std::vector<unsigned int> _VAOs, _EBOs, _VBOs;
        std::vector<std::vector<InpolVertex>> _vertices;
        std::vector<std::vector<unsigned int>> _indices;
        Point _position;
        Scale _scale;
        Rotation _rotation;
        unsigned int _textureIdx;
        std::vector<Texture> _textures;
};
} // namespace Eendgine
