#pragma once
#include<glm/glm.hpp>

namespace Eendgine {
    struct Vertex {
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec4 color = glm::vec4(0.0f);
        glm::vec2 uv = glm::vec2(0.0f);
        glm::vec3 normal = glm::vec3(0.0f);
    };

    struct InpolVertex {
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 nextPosition = glm::vec3(0.0f);
        glm::vec4 color = glm::vec4(0.0f);
        glm::vec2 uv = glm::vec2(0.0f);
        glm::vec3 normal = glm::vec3(0.0f);
        glm::vec3 nextNormal = glm::vec3(0.0f);
    };
}
