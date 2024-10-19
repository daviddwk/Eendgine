#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Eendgine {
Camera2D::Camera2D(int width, int height)
    : _width(width), _height(height), _scale(1.0f), _position(glm::vec3(0.0f)),
      _orthoMatrix(glm::mat4(0.0f)), _cameraMatrix(glm::mat4(0.0f))

{
    _orthoMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
    update();
}

void Camera2D::update() {
    glm::vec3 translate =
        glm::vec3(-_position.x + (_width / 2.0f), -_position.y + (_height / 2.0f), 0.0f);
    _cameraMatrix = glm::translate(_orthoMatrix, translate);

    glm::vec3 scale = glm::vec3(_scale, _scale, 0.0f);
    _cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
}

glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenChoords) {
    screenChoords.y = _height - screenChoords.y;
    screenChoords -= glm::vec2(_width / 2, _height / 2);
    screenChoords /= _scale;
    screenChoords += _position;

    return screenChoords;
}

Camera3D::Camera3D(float aspectRatio, glm::vec3 position, glm::vec3 target)
    : _aspectRatio(aspectRatio), _position(position), _target(target), _viewMat(glm::mat4(0.0f)),
      _projectionMat(glm::mat4(0.0f)) {
    update();
}

void Camera3D::update() {
    _projectionMat = glm::perspective(glm::radians(45.0f), _aspectRatio, 1.0f, 1000.0f);
    _viewMat = glm::lookAt(_position, _target, glm::vec3(0.0f, 1.0f, 0.0f));
}
} // namespace Eendgine
