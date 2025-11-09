#include "Eendgine/camera.hpp"
#include "Eendgine/vertex.hpp"
#include "doll.hpp"
#include "fatalError.hpp"
#include "loadModel.hpp"
#include <GLES3/gl3.h>
#include <filesystem>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <json/json.h>

namespace Eendgine {
Doll::Doll(std::filesystem::path path)
    : m_numIndices(0), m_position(Point(0.0f)), m_scale(Scale(1.0f)), m_rotation(Rotation(0.0f)),
      m_animScale(0.0f), m_textureIdx(0) {

    std::map<std::string, std::vector<std::vector<InpolVertex>>> vertices;
    std::map<std::string, std::vector<std::vector<unsigned int>>> indices;
    std::filesystem::path dollPath = std::filesystem::path("resources") / path;
    if (!std::filesystem::is_directory(dollPath)) {
        fatalError("Doll directory " + dollPath.string() + " is not a directory");
    }

    std::vector<std::filesystem::path> animationPaths;
    bool first = true;
    for (const auto& entry : std::filesystem::directory_iterator(dollPath)) {
        if (entry.is_directory()) {
            if (first) {
                m_animation = entry.path().filename();
            }
            animationPaths.push_back(entry.path());
        }
    }

    for (const auto& animationPath : animationPaths) {
        // metadata
        Json::Value root;
        std::filesystem::path metadataPath = animationPath / "metadata.json";
        std::ifstream metadata(metadataPath);
        if (!metadata.is_open()) {
            fatalError("could not open: " + metadataPath.string());
        }
        try {
            metadata >> root;
        } catch (...) {
            fatalError("improper json: " + metadataPath.string());
        }
        if (!root["loop"].is<bool>()) {
            fatalError("no loop in: " + metadataPath.string());
        }
        bool loop = root["loop"].asBool();

        // animations
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

        const unsigned int numInpols = loop ? modelPaths.size() : modelPaths.size() - 1;

        m_VAOs[animationName].resize(numInpols, 0);
        m_VBOs[animationName].resize(numInpols, 0);
        m_EBOs[animationName].resize(numInpols, 0);
        vertices[animationName].resize(numInpols);
        indices[animationName].resize(numInpols);

        for (unsigned int i = 0; i < numInpols; i++) {
            // use next model looping back to the first
            loadModel(
                modelPaths[i],
                modelPaths[(i + 1) % modelPaths.size()],
                vertices[animationName][i],
                indices[animationName][i],
                m_textures);

            glGenVertexArrays(1, &m_VAOs[animationName][i]);
            glBindVertexArray(m_VAOs[animationName][i]);

            glGenBuffers(1, &m_VBOs[animationName][i]);
            glGenBuffers(1, &m_EBOs[animationName][i]);

            glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[animationName][i]);
            glBufferData(
                GL_ARRAY_BUFFER,
                vertices[animationName][i].size() * sizeof(InpolVertex),
                &vertices[animationName][i][0],
                GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOs[animationName][i]);
            glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                indices[animationName][i].size() * sizeof(unsigned int),
                &indices[animationName][i][0],
                GL_STATIC_DRAW);

            glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(InpolVertex),
                (void*)offsetof(InpolVertex, position));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(
                1,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(InpolVertex),
                (void*)offsetof(InpolVertex, nextPosition));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(
                2,
                4,
                GL_FLOAT,
                GL_FALSE,
                sizeof(InpolVertex),
                (void*)offsetof(InpolVertex, color));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(
                3,
                2,
                GL_FLOAT,
                GL_FALSE,
                sizeof(InpolVertex),
                (void*)offsetof(InpolVertex, uv));
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(
                4,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(InpolVertex),
                (void*)offsetof(InpolVertex, normal));
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(
                5,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(InpolVertex),
                (void*)offsetof(InpolVertex, nextNormal));
            glEnableVertexAttribArray(5);
        }
    }
    m_numIndices = indices.begin()->second[0].size();
    for (auto& indicesAnimation : indices) {
        for (auto& indicesModel : indicesAnimation.second) {
            if (indicesModel.size() != m_numIndices)
                fatalError(
                    std::format(
                        "mismatch in vertex number for animation {}",
                        dollPath.generic_string()));
        }
    }
}

Doll::~Doll() {
    for (auto& [key, vaos] : m_VAOs) {
        glDeleteVertexArrays(vaos.size(), vaos.data());
    }
    for (auto& [key, vbos] : m_VBOs) {
        glDeleteBuffers(vbos.size(), vbos.data());
    }
    for (auto& [key, ebos] : m_EBOs) {
        glDeleteBuffers(ebos.size(), ebos.data());
    }
}

Doll::Doll(Doll&& other) noexcept
    : m_animation(std::move(other.m_animation)), m_VAOs(std::move(other.m_VAOs)),
      m_VBOs(std::move(other.m_VBOs)), m_EBOs(std::move(other.m_EBOs)),
      m_numIndices(std::move(other.m_numIndices)), m_position(std::move(other.m_position)),
      m_scale(std::move(other.m_scale)), m_rotation(std::move(other.m_rotation)),
      m_animScale(std::move(other.m_animScale)), m_textureIdx(std::move(other.m_textureIdx)),
      m_textures(std::move(other.m_textures)) {
    other.m_VAOs.clear();
    other.m_VBOs.clear();
    other.m_EBOs.clear();
};

Doll& Doll::operator=(Doll&& other) noexcept {

    if (&other == this) return *this;

    for (auto& [key, vaos] : m_VAOs) {
        glDeleteVertexArrays(vaos.size(), vaos.data());
    }
    for (auto& [key, vbos] : m_VBOs) {
        glDeleteBuffers(vbos.size(), vbos.data());
    }
    for (auto& [key, ebos] : m_EBOs) {
        glDeleteBuffers(ebos.size(), ebos.data());
    }

    m_animation = other.m_animation;
    m_VAOs = other.m_VAOs;
    m_VBOs = other.m_VBOs;
    m_EBOs = other.m_EBOs;
    m_numIndices = other.m_numIndices;
    m_position = other.m_position;
    m_scale = other.m_scale;
    m_rotation = other.m_rotation;
    m_animScale = other.m_animScale;
    m_textureIdx = other.m_textureIdx;
    m_textures = other.m_textures;

    other.m_VAOs.clear();
    other.m_VBOs.clear();
    other.m_EBOs.clear();

    return *this;
};

void Doll::draw(uint shaderId, Camera3D& camera) {
    // using RGB(1,0,1) for transparent
    // parts of the texture using shaders
    TransformationMatrix transform = TransformationMatrix(1.0f);
    transform = glm::translate(transform, m_position);
    // this is a sign that I should be having 3 axis rotation
    transform = glm::rotate(transform, -m_rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, -m_rotation.y, glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, -m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, m_scale);

    unsigned int projectionLoc = glGetUniformLocation(shaderId, "projection");
    unsigned int viewLoc = glGetUniformLocation(shaderId, "view");
    unsigned int transformLoc = glGetUniformLocation(shaderId, "transform");
    unsigned int inpolLoc = glGetUniformLocation(shaderId, "inpol");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera.getProjectionMat()[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.getViewMat()[0][0]);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
    float scaledAnimScale = m_VAOs[m_animation].size() * m_animScale;
    glUniform1f(inpolLoc, scaledAnimScale - ((int)scaledAnimScale));
    glBindVertexArray(m_VAOs[m_animation][(int)scaledAnimScale]);

    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
}; // namespace Eendgine
