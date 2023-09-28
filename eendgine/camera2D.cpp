#include <eendgine/camera2D.hpp>

namespace Eendgine {
    void Camera2D::init(int width, int height){

        _position = glm::vec2(width, height); 
        _orthoMatrix = glm::ortho(0, width, 0, height);

        _needsUpdate = true;
    }

    void Camera2D::update() {
        glm::vec3 translate = glm::vec3(x, y, 0.0f);
        _cameraMatrix = glm::translate(_orthoMatrix, translate);
    }
}
