#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Eendgine {
Camera2D::Camera2D(int width, int height)
    : m_width(width), m_height(height), m_scale(1.0f), m_position(Point(0.0f)),
      m_orthoMatrix(TransformationMatrix(0.0f)), m_cameraMatrix(TransformationMatrix(0.0f))

{
    m_orthoMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1000.0f, 1000.0f);
    update();
}

void Camera2D::update() {
    glm::vec3 translate =
        Point(-m_position.x + (m_width / 2.0f), -m_position.y + (m_height / 2.0f), 0.0f);
    m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

    glm::vec3 scale = Scale(m_scale, m_scale, 1.0f);
    m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
}

glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenChoords) {
    screenChoords.y = m_height - screenChoords.y;
    screenChoords -= glm::vec2(m_width / 2, m_height / 2);
    screenChoords /= m_scale;
    screenChoords += m_position;

    return screenChoords;
}

Camera3D::Camera3D(float aspectRatio, Point position, Point target)
    : m_aspectRatio(aspectRatio), m_position(position), m_target(target),
      m_viewMat(glm::mat4(0.0f)), m_projectionMat(glm::mat4(0.0f)) {
    update();
}

void Camera3D::update() {
    m_projectionMat = glm::perspective(glm::radians(45.0f), m_aspectRatio, 1.0f, 1000.0f);
    m_viewMat = glm::lookAt(m_position, m_target, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Cameras::construct(const Camera2D& hudCamera, const Camera3D& sceneCamera) {
    assert(m_instance2D == nullptr);
    m_instance2D = new Camera2D(hudCamera);
    assert(m_instance3D == nullptr);
    m_instance3D = new Camera3D(sceneCamera);
}

void Cameras::destruct() {
    assert(m_instance2D != nullptr);
    delete m_instance2D;
    m_instance2D = nullptr;
    assert(m_instance3D != nullptr);
    delete m_instance3D;
    m_instance3D = nullptr;
}

Camera2D& Cameras::getHud() {
    assert(m_instance2D != nullptr);
    return *m_instance2D;
}

Camera3D& Cameras::getScene() {
    assert(m_instance3D != nullptr);
    return *m_instance3D;
}

} // namespace Eendgine
