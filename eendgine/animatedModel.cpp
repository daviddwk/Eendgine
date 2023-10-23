#include <eendgine/animatedModel.hpp>

#include <cmath>

namespace Eendgine {
    AnimatedModel::AnimatedModel(std::vector<std::string> modelPaths, TextureCache texCache) {
        _animTime = 0.0f;
        for (int i = 0; i < modelPaths.size() - 1; i++) {
            _lerpModels.emplace_back(LerpModel(modelPaths[i], modelPaths[i + 1], texCache));
        }
    }

    void AnimatedModel::draw(ShaderProgram &shader, Camera3D &camera) {
        float wrappedAnimTime = std::abs(_animTime - (int)_animTime);
        float scaledAnimTime = _lerpModels.size() * wrappedAnimTime;
        _lerpModels[(int)scaledAnimTime].setLerp(scaledAnimTime - ((int)scaledAnimTime));
        _lerpModels[(int)scaledAnimTime].draw(shader, camera);
    }
}
