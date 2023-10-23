#include <eendgine/animatedModel.hpp>

#include <cmath>

namespace Eendgine {
    AnimatedModel::AnimatedModel(std::vector<std::string> modelPaths, TextureCache texCache) {
        _animScale = 0.0f;
        for (int i = 0; i < modelPaths.size() - 1; i++) {
            _inpolModels.emplace_back(InpolModel(modelPaths[i], modelPaths[i + 1], texCache));
        }
    }

    void AnimatedModel::draw(ShaderProgram &shader, Camera3D &camera) {
        float wrappedAnimScale = std::abs(_animScale - (int)_animScale);
        float scaledAnimScale = _inpolModels.size() * wrappedAnimScale;
        _inpolModels[(int)scaledAnimScale].setInpol(scaledAnimScale - ((int)scaledAnimScale));
        _inpolModels[(int)scaledAnimScale].draw(shader, camera);
    }
}
