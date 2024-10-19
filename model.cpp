#include "fatalError.hpp"
#include "loadModel.hpp"
#include "model.hpp"
#include "shader.hpp"
#include <GLES3/gl3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Eendgine {
Model::Model(std::string modelPath)
    : _position(glm::vec3(0.0f)), _scale(glm::vec3(1.0f)), _rotation(glm::vec2(0.0f)),
      _textureIdx(0), _VAO(0), _VBO(0), _EBO(0) {

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
        0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);
}

void Model::draw(uint shaderId, Camera3D &camera) {
    // using RGB(1,0,1) for transparent
    // parts of the texture using shaders

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, _position);
    transform = glm::rotate(transform, -_rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, -_rotation.y, glm::vec3(-1.0f, 0.0f, 0.0f));
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

Animation::Animation(std::filesystem::path modelsDir)
    : _position(glm::vec3(0.0f)), _scale(glm::vec3(1.0f)), _rotation(glm::vec2(0.0f)),
      _textureIdx(0), _animScale(0.0f) {
    std::vector<std::string> modelPaths;

    if (!std::filesystem::is_directory(modelsDir)) {
        fatalError("animation dir not a dir");
    }
    int modelNum = 0;
    std::string nextModelName = modelsDir.filename().string() + std::to_string(modelNum) + ".obj";
    auto modelPath = modelsDir / std::filesystem::path(nextModelName);
    while (std::filesystem::is_regular_file(modelPath)) {
        modelPaths.push_back(modelPath.string());
        modelNum++;
        nextModelName = modelsDir.filename().string() + std::to_string(modelNum) + ".obj";
        modelPath = modelsDir / std::filesystem::path(nextModelName);
    }

    _VAOs.resize(modelPaths.size(), 0);
    _VBOs.resize(modelPaths.size(), 0);
    _EBOs.resize(modelPaths.size(), 0);
    _vertices.resize(modelPaths.size());
    _indices.resize(modelPaths.size());

    for (int i = 0; i < modelPaths.size(); i++) {
        // use next model looping back to the first
        loadModel(modelPaths[i], modelPaths[(i + 1) % modelPaths.size()], _vertices[i], _indices[i],
            _textures);

        glGenVertexArrays(1, &_VAOs[i]);
        glBindVertexArray(_VAOs[i]);

        glGenBuffers(1, &_VBOs[i]);
        glGenBuffers(1, &_EBOs[i]);

        glBindBuffer(GL_ARRAY_BUFFER, _VBOs[i]);
        glBufferData(GL_ARRAY_BUFFER, _vertices[i].size() * sizeof(InpolVertex), &_vertices[i][0],
            GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBOs[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices[i].size() * sizeof(unsigned int),
            &_indices[i][0], GL_STATIC_DRAW);

        glVertexAttribPointer(
            0, 3, GL_FLOAT, GL_FALSE, sizeof(InpolVertex), (void *)offsetof(InpolVertex, position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(InpolVertex),
            (void *)offsetof(InpolVertex, nextPosition));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            2, 4, GL_FLOAT, GL_FALSE, sizeof(InpolVertex), (void *)offsetof(InpolVertex, color));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(
            3, 2, GL_FLOAT, GL_FALSE, sizeof(InpolVertex), (void *)offsetof(InpolVertex, uv));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(
            4, 3, GL_FLOAT, GL_FALSE, sizeof(InpolVertex), (void *)offsetof(InpolVertex, normal));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(InpolVertex),
            (void *)offsetof(InpolVertex, nextNormal));
        glEnableVertexAttribArray(5);
    }
}

void Animation::draw(uint shaderId, Camera3D &camera) {
    // using RGB(1,0,1) for transparent
    // parts of the texture using shaders
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, _position);
    transform = glm::rotate(transform, -_rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, -_rotation.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    transform = glm::scale(transform, _scale);

    unsigned int projectionLoc = glGetUniformLocation(shaderId, "projection");
    unsigned int viewLoc = glGetUniformLocation(shaderId, "view");
    unsigned int transformLoc = glGetUniformLocation(shaderId, "transform");
    unsigned int inpolLoc = glGetUniformLocation(shaderId, "inpol");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera.getProjectionMat()[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.getViewMat()[0][0]);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

    float scaledAnimScale = _VAOs.size() * _animScale;
    glUniform1f(inpolLoc, scaledAnimScale - ((int)scaledAnimScale));
    glBindVertexArray(_VAOs[(int)scaledAnimScale]);

    glDrawElements(GL_TRIANGLES, _indices[(int)scaledAnimScale].size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
} // namespace Eendgine
