#pragma once

#include <glm/glm.hpp>

namespace Eendgine {
    class Camera3D {
        public:
            Camera3D(float width, float height, glm::vec3 position, glm::vec3 target);
            glm::mat4 viewMat = glm::mat4(0.0f);
            glm::mat4 projectionMat = glm::mat4(0.0f);
            
            // concider not updating and making do manually
            void setAspectRatio(float width, float height) { _aspectRatio = width / height; update(); };
            void setPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); update(); };
            void setTarget(float x, float y, float z) { _target = glm::vec3(x, y, z); update(); };

            float getAspectRatio() { return _aspectRatio; };
            glm::vec3 getPosition() {return _position; };
            glm::vec3 getTarget() {return _target; };

        private:
            void update();

            float _aspectRatio = 1.0f;
            glm::vec3 _position = glm::vec3(0.0f);
            glm::vec3 _target = glm::vec3(0.0f);
    };
}
