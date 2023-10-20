#include <eendgine/camera3D.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Eendgine {
    Camera3D::Camera3D(float width, float height, glm::vec3 position, glm::vec3 target) {
        _aspectRatio = width / height;
        _position = position;
        _target = target;
        update();
    }

    void Camera3D::update() {
        projectionMat = glm::perspective(glm::radians(45.0f), _aspectRatio, 1.0f, 1000.0f);
        // position, target, up direction
        viewMat = glm::lookAt(_position, _target, glm::vec3(0.0, 0.1, 0.0));
    }
}
