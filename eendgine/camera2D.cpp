#include <eendgine/camera2D.hpp>

namespace Eendgine {
    void Camera2D::init(int width, int height){

        _width = width;
        _height = height;

        _orthoMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height);

        _needsUpdate = true;
    }

    void Camera2D::update() {
        if (_needsUpdate) {
            glm::vec3 translate = glm::vec3(-_position.x + (_width / 2.0f), -_position.y + (_height / 2.0f), 0.0f);
            _cameraMatrix = glm::translate(_orthoMatrix, translate);

            glm::vec3 scale = glm::vec3(_scale, _scale, 0.0f);
            _cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

            _needsUpdate = false;
        }
    }

    glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenChoords) {
        screenChoords.y = _height - screenChoords.y;
        screenChoords -= glm::vec2(_width / 2, _height / 2);
        screenChoords /= _scale;
        screenChoords += _position;

        return screenChoords;
    }
}
