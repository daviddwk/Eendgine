#pragma once
#include "model.hpp"
#include "shader.hpp"
#include "camera.hpp"

#include <set>

namespace Eendgine {
    class RenderBatch {
        public:
            RenderBatch();
            void insertModel(Model* model);
            void eraseModel(Model* model);
            void render(ShaderProgram &shader, Camera3D &camera);

        private:
            inline static auto _compare = [](Model* a, Model* b)
                {
                    return a->getTexture() > b->getTexture();
                }; 
            std::set<Model*, decltype(_compare)> _models;
    };
}
