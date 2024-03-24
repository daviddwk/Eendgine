#pragma once
#include "model.hpp"
#include "shader.hpp"
#include "camera.hpp"

namespace Eendgine {
    void renderModelBatch(std::vector<Model*>* models, ShaderProgram &shader, Camera3D &camera);
}
