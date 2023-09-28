#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Eendgine {
    class Camera2D {
        public:
            void init(int width, int height);
            void update();
            void convertScreenToWorld();
            
            void setPosition(float x, float y);
            void setScale();
            
            glm::mat4 getWorld();
            



        private:
            bool _needsUpdate;
            float _scale;
            glm::vec2 _position;
            glm::mat4 _orthoMatrix;
            glm::mat4 _cameraMatrix;
    };
}
