#include "animatedModel.hpp"
#include <cmath>

namespace Eendgine {
    AnimatedModel::AnimatedModel(std::vector<std::string> modelPaths, TextureCache texCache) :
        _animScale(0.0f)
    {
        for (int i = 0; i < modelPaths.size(); i++) {
            int next = i + 1;
            if (i == modelPaths.size() - 1){
                next = 0;
            }
            _inpolModels.emplace_back(InpolModel(modelPaths[i], modelPaths[next], texCache));
        }
    }

    void AnimatedModel::draw(ShaderProgram &shader, Camera3D &camera) {
        float wrappedAnimScale = _animScale - (int)_animScale;
        if (wrappedAnimScale < 0.0f) {
            wrappedAnimScale += 1.0f;
        }
        // annoying edge case
        if (wrappedAnimScale == 1) {
            wrappedAnimScale = 0;
        }
        float scaledAnimScale = _inpolModels.size() * wrappedAnimScale;
        _inpolModels[(int)scaledAnimScale].setInpol(scaledAnimScale - ((int)scaledAnimScale));
        _inpolModels[(int)scaledAnimScale].draw(shader, camera);
    }
}
