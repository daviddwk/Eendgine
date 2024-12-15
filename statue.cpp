#include "fatalError.hpp"
#include "loadModel.hpp"
#include "statue.hpp"
#include "types.hpp"
#include <GLES3/gl3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Eendgine {
Statue::Statue(const std::string path)
    : _VAO(0), _VBO(0), _EBO(0), _position(Point(0.0f)), _scale(Scale(1.0f)),
      _rotation(Rotation(0.0f)), _textureIdx(0), _name(path) {

    const std::filesystem::path modelPath =
        std::filesystem::path("resources") / path /
        (std::filesystem::path(path).filename().string() + ".obj");
    loadModel(modelPath, _vertices, _indices, _textures);

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0],
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
    glDeleteVertexArrays(1, &_VAO);
    glDeleteFramebuffers(1, &_VBO);
    glDeleteFramebuffers(1, &_EBO);
}

void Statue::draw(uint shaderId, Camera3D& camera) {
    // using RGB(1,0,1) for transparent
    // parts of the texture using shaders

    TransformationMatrix transform = TransformationMatrix(1.0f);
    transform = glm::translate(transform, _position);
    transform = glm::rotate(transform, -_rotation.x, Point(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, -_rotation.y, Point(-1.0f, 0.0f, 0.0f));
    transform = glm::scale(transform, _scale);

    unsigned int projectionLoc = glGetUniformLocation(shaderId, "projection");
    unsigned int viewLoc = glGetUniformLocation(shaderId, "view");
    unsigned int transformLoc = glGetUniformLocation(shaderId, "transform");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera.getProjectionMat()[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.getViewMat()[0][0]);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

} // namespace Eendgine
