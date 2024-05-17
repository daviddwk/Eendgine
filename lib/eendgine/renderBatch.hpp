#pragma once
#include "model.hpp"
#include "shader.hpp"
#include "camera.hpp"

#include <set>
#include <functional>

namespace Eendgine {
    struct ModelComparator {
        bool operator()(Model* m1, Model* m2) const {
            return m1->getTexture() > m2->getTexture();
        }
    };
    class RenderBatch {
        public:
            RenderBatch();
            void insertModel(Model* model);
            void eraseModel(Model* model);
            void render(ShaderProgram &shader, Camera3D &camera);

        private:
            std::set<Model*, ModelComparator> _models;
    };
}
