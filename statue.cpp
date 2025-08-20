#include "loadModel.hpp"
#include "statue.hpp"
#include "types.hpp"
#include "vertex.hpp"
#include <GLES3/gl3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Eendgine {
Statue::Statue(const std::string path)
    : m_VAO(0), m_VBO(0), m_EBO(0), m_numIndices(0), m_position(Point(0.0f)), m_scale(Scale(1.0f)),
      m_rotation(Rotation(0.0f)), m_textureIdx(0) {

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    const std::filesystem::path modelPath =
        std::filesystem::path("resources") / path /
        (std::filesystem::path(path).filename().string() + ".obj");
    loadModel(modelPath, vertices, indices, m_textures);
    m_numIndices = indices.size();

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0],
        GL_STATIC_DRAW);

    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);
}

Statue::~Statue() {}

void Statue::eraseBuffers() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteFramebuffers(1, &m_VBO);
    glDeleteFramebuffers(1, &m_EBO);
}

void Statue::draw(uint shaderId, Camera3D& camera) {
    // using RGB(1,0,1) for transparent
    // parts of the texture using shaders

    TransformationMatrix transform = TransformationMatrix(1.0f);
    transform = glm::translate(transform, m_position);
    transform = glm::rotate(transform, -m_rotation.x, Point(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, -m_rotation.y, Point(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, -m_rotation.z, Point(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, m_scale);

    unsigned int projectionLoc = glGetUniformLocation(shaderId, "projection");
    unsigned int viewLoc = glGetUniformLocation(shaderId, "view");
    unsigned int transformLoc = glGetUniformLocation(shaderId, "transform");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera.getProjectionMat()[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.getViewMat()[0][0]);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

} // namespace Eendgine
