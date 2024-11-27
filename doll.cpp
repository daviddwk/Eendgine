#include "Eendgine/camera.hpp"
#include "doll.hpp"
#include "fatalError.hpp"
#include "info.hpp"
#include "loadModel.hpp"
#include <GLES3/gl3.h>
#include <filesystem>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Eendgine {
Doll::Doll(std::filesystem::path dollPath)
    : _position(Point(0.0f)), _scale(Scale(1.0f)), _rotation(Rotation(0.0f)), _animScale(0.0f),
      _textureIdx(0) {

    if (!std::filesystem::is_directory(dollPath)) {
        fatalError("Doll directory " + dollPath.string() + " is not a directory");
    }

    std::vector<std::filesystem::path> animationPaths;
    bool first = true;
    for (const auto& entry : std::filesystem::directory_iterator(dollPath)) {
        if (entry.is_directory()) {
            if (first) {
                _animation = entry.path().filename();
            }
            animationPaths.push_back(entry.path());
        }
    }

    for (const auto& animationPath : animationPaths) {
        std::string animationName = animationPath.filename();

        std::vector<std::filesystem::path> modelPaths;

        int modelNum = 0;

        std::string nextModelName =
            dollPath.filename().string() + std::to_string(modelNum) + ".obj";
        auto modelPath = animationPath / std::filesystem::path(nextModelName);
        while (std::filesystem::is_regular_file(modelPath)) {
            modelPaths.push_back(modelPath.string());
            modelNum++;
            nextModelName = dollPath.filename().string() + std::to_string(modelNum) + ".obj";
            modelPath = animationPath / std::filesystem::path(nextModelName);
        }

        _VAOs[animationName].resize(modelPaths.size(), 0);
        _VBOs[animationName].resize(modelPaths.size(), 0);
        _EBOs[animationName].resize(modelPaths.size(), 0);
        _vertices[animationName].resize(modelPaths.size());
        _indices[animationName].resize(modelPaths.size());

        for (unsigned int i = 0; i < modelPaths.size(); i++) {
            // use next model looping back to the first
            loadModel(modelPaths[i], modelPaths[(i + 1) % modelPaths.size()],
                _vertices[animationName][i], _indices[animationName][i], _textures);

            glGenVertexArrays(1, &_VAOs[animationName][i]);
            glBindVertexArray(_VAOs[animationName][i]);

            glGenBuffers(1, &_VBOs[animationName][i]);
            glGenBuffers(1, &_EBOs[animationName][i]);

            glBindBuffer(GL_ARRAY_BUFFER, _VBOs[animationName][i]);
            glBufferData(GL_ARRAY_BUFFER, _vertices[animationName][i].size() * sizeof(InpolVertex),
                &_vertices[animationName][i][0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBOs[animationName][i]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                _indices[animationName][i].size() * sizeof(unsigned int),
                &_indices[animationName][i][0], GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(InpolVertex),
                (void*)offsetof(InpolVertex, position));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(InpolVertex),
                (void*)offsetof(InpolVertex, nextPosition));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(
                2, 4, GL_FLOAT, GL_FALSE, sizeof(InpolVertex), (void*)offsetof(InpolVertex, color));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(
                3, 2, GL_FLOAT, GL_FALSE, sizeof(InpolVertex), (void*)offsetof(InpolVertex, uv));
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(InpolVertex),
                (void*)offsetof(InpolVertex, normal));
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(InpolVertex),
                (void*)offsetof(InpolVertex, nextNormal));
            glEnableVertexAttribArray(5);
        }
    }
}

void Doll::draw(uint shaderId, Camera3D& camera) {
    // using RGB(1,0,1) for transparent
    // parts of the texture using shaders
    TransformationMatrix transform = TransformationMatrix(1.0f);
    transform = glm::translate(transform, _position);
    // this is a sign that I should be having 3 axis rotation
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
    float scaledAnimScale = _VAOs[_animation].size() * _animScale;
    Info::registerFloat("scaledAnim", INFO_OPTION_NONE);
    Info::updateFloat("scaledAnim", scaledAnimScale);
    glUniform1f(inpolLoc, scaledAnimScale - ((int)scaledAnimScale));
    glBindVertexArray(_VAOs[_animation][(int)scaledAnimScale]);

    glDrawElements(
        GL_TRIANGLES, _indices[_animation][(int)scaledAnimScale].size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
}; // namespace Eendgine
