#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Eendgine {
    class Camera2D {
        public:
            Camera2D(int width, int height);
            void update();
            glm::vec2 convertScreenToWorld(glm::vec2 screenChoords);
            
            void setPosition(float x, float y) { _position = glm::vec2(x, y); _needsUpdate = true; }
            void setScale(float scale) { _scale = scale; _needsUpdate = true; }

            glm::vec2 getPosition() { return _position; }
            float getScale() { return  _scale; }
            glm::mat4 getCameraMatrix() { return _cameraMatrix; }
            
        private:
            bool _needsUpdate = true;
            float _scale = 1.0f;
            int _width = 0, _height = 0;
            glm::vec2 _position = glm::vec2(0.0f);
            glm::mat4 _orthoMatrix = glm::mat4(0.0f);
            glm::mat4 _cameraMatrix = glm::mat4(0.0f);
    };
}
