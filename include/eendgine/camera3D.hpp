#pragma once

#include <glm/glm.hpp>

namespace Eendgine {
    class Camera3D {
        public:
            Camera3D(float width, float height, glm::vec3 position, glm::vec3 target);
            glm::mat4 viewMat;
            glm::mat4 projectionMat;
    };
}
