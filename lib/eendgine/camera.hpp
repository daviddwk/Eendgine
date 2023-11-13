#pragma once
#include <glm/glm.hpp>

namespace Eendgine {
    class Camera2D {
        public:
            Camera2D(int width, int height);
            glm::vec2 convertScreenToWorld(glm::vec2 screenChoords);
            
            void setPosition(float x, float y) { _position = glm::vec2(x, y); update(); }
            void setScale(float scale) { _scale = scale; update(); }

            glm::vec2 getPosition() { return _position; }
            float getScale() { return  _scale; }
            glm::mat4 getCameraMatrix() { return _cameraMatrix; }
            
        private:
            void update();

            int _width, _height;
            float _scale;
            glm::vec2 _position;
            glm::mat4 _orthoMatrix;
            glm::mat4 _cameraMatrix;
    };
    class Camera3D {
        public:
            Camera3D(float aspectRatio, glm::vec3 position, glm::vec3 target);
            
            // concider not updating and making do manually
            void setAspectRatio(float aspectRatio) { _aspectRatio = aspectRatio; update(); };
            void setPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); update(); };
            void setTarget(float x, float y, float z) { _target = glm::vec3(x, y, z); update(); };

            float getAspectRatio() { return _aspectRatio; };
            glm::vec3 getPosition() { return _position; };
            glm::vec3 getTarget() { return _target; };
            glm::mat4 getViewMat() { return _viewMat; };
            glm::mat4 getProjectionMat() { return _projectionMat; };

        private:
            void update();

            float _aspectRatio;
            glm::vec3 _position;
            glm::vec3 _target;
            glm::mat4 _viewMat;
            glm::mat4 _projectionMat;
    };
}
