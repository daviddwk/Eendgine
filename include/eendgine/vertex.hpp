#pragma once

#include<glm/glm.hpp>

namespace Eendgine {
    struct Vertex {
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec4 color = glm::vec4(0.0f);
        glm::vec2 uv = glm::vec2(0.0f);
        glm::vec3 normal = glm::vec3(0.0f);
        
        void setPosition(float x, float y, float z) {
            position = glm::vec3(x, y, z);
        }

        void setColor(float r, float g, float b, float a) {
            color = glm::vec4(r, g, b, a);
        }

        void setUv(float u, float v) {
            uv = glm::vec2(u, v);
        }

        void setNormal(float x, float y, float z) {
            normal = glm::vec3(x, y, z); 
        }
    };
}
