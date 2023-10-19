#include <eendgine/camera3D.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Eendgine {
    Camera3D::Camera3D(float width, float height, glm::vec3 position, glm::vec3 target) {
        //
        projectionMat = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
        // position, target, up direction
        viewMat = glm::lookAt(position, target, glm::vec3(0.0, 0.1, 0.0));
        
    }
}
