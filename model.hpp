#pragma once
#include "camera.hpp"
#include "shader.hpp"
#include "textureCache.hpp"
#include "vertex.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <filesystem>
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace Eendgine {
class Model {
  public:
    Model(std::string modelPath);

    void setPosition(glm::vec3 position) { _position = position; };
    void setScale(glm::vec3 scale) { _scale = scale; };
    void setRadians(float x, float y) { _rotation = glm::vec2(x, y); };
    void setRotation(float x, float y) { _rotation = glm::vec2(glm::radians(x), glm::radians(y)); };

    void setTextureIdx(unsigned int idx) { _textureIdx = (idx < _textures.size() ? idx : 0); };

    glm::vec3 getPosition() { return _position; };
    glm::vec3 getScale() { return _scale; };
    glm::vec2 getRotation() { return _rotation; };

    Texture getTexture() { return _textures[_textureIdx]; };
    unsigned int getTextureIdx() { return _textureIdx; };

    void draw(uint shaderId, Camera3D &camera);

  private:
    unsigned int _VAO, _EBO, _VBO;
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    glm::vec3 _position;
    glm::vec3 _scale;
    glm::vec2 _rotation;
    unsigned int _textureIdx;
    std::vector<Texture> _textures;
};

class Animation {
  public:
    Animation(std::filesystem::path modelsDir);

    void setPosition(glm::vec3 position) { _position = position; };
    void setScale(glm::vec3 scale) { _scale = scale; };
    void setRadians(float x, float y) { _rotation = glm::vec2(x, y); };
    void setRotation(float x, float y) { _rotation = glm::vec2(glm::radians(x), glm::radians(y)); };

    void setTextureIdx(unsigned int idx) { _textureIdx = (idx < _textures.size() ? idx : 0); };

    glm::vec3 getPosition() { return _position; };
    glm::vec3 getScale() { return _scale; };
    glm::vec2 getRotation() { return _rotation; };

    Texture getTexture() { return _textures[_textureIdx]; };
    unsigned int getTextureIdx() { return _textureIdx; };
    float getAnim() { return _animScale; };

    void draw(uint shaderId, Camera3D &camera);

    void setAnim(float scale) { _animScale = scale - (int)scale; };

  private:
    float _animScale;
    std::vector<unsigned int> _VAOs, _EBOs, _VBOs;
    std::vector<std::vector<InpolVertex>> _vertices;
    std::vector<std::vector<unsigned int>> _indices;
    glm::vec3 _position;
    glm::vec3 _scale;
    glm::vec2 _rotation;
    unsigned int _textureIdx;
    std::vector<Texture> _textures;
};
} // namespace Eendgine
