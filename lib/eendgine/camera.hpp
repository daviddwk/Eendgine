#pragma once
#include <glm/glm.hpp>

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
    class Camera3D {
        public:
            Camera3D(float aspectRatio, glm::vec3 position, glm::vec3 target);
            glm::mat4 viewMat = glm::mat4(0.0f);
            glm::mat4 projectionMat = glm::mat4(0.0f);
            
            // concider not updating and making do manually
            void setAspectRatio(float aspectRatio) { _aspectRatio = aspectRatio; update(); };
            void setPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); update(); };
            void setTarget(float x, float y, float z) { _target = glm::vec3(x, y, z); update(); };

            float getAspectRatio() { return _aspectRatio; };
            glm::vec3 getPosition() { return _position; };
            glm::vec3 getTarget() { return _target; };

        private:
            void update();

            float _aspectRatio = 1.0f;
            glm::vec3 _position = glm::vec3(0.0f);
            glm::vec3 _target = glm::vec3(0.0f);
    };
}
