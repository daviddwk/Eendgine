#pragma once
#include "vertex.hpp"
#include "textureCache.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
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

            void setTextureIdx(unsigned int idx) { 
                _textureIdx = (idx < _textures.size() ? idx : 0); 
            };

            glm::vec3 getPosition() { return _position; };
            glm::vec3 getScale() { return _scale; };
            glm::vec2 getRotation() { return _rotation; };
            
            unsigned int getTexture() { return _textures[_textureIdx].id; };
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
            Animation(std::vector<std::string> modelPaths);

            void setPosition(glm::vec3 position) { _position = position; };
            void setScale(glm::vec3 scale) { _scale = scale; };
            void setRadians(float x, float y) { _rotation = glm::vec2(x, y); };
            void setRotation(float x, float y) { _rotation = glm::vec2(glm::radians(x), glm::radians(y)); };

            void setTextureIdx(unsigned int idx) { 
                _textureIdx = (idx < _textures.size() ? idx : 0); 
            };

            glm::vec3 getPosition() { return _position; };
            glm::vec3 getScale() { return _scale; };
            glm::vec2 getRotation() { return _rotation; };

            unsigned int getTexture() { return _textures[_textureIdx].id; };
            unsigned int getTextureIdx() { return _textureIdx; };
            float getAnim() { return _animScale; };
            
            void draw(uint shaderId, Camera3D &camera);
            
            void setAnim(float scale) { _animScale = scale - (int) scale; };
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
}
