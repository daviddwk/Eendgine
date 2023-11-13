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
            Model(std::string modelPath, TextureCache &texCache);
            void draw(ShaderProgram &shader, Camera3D &camera);

            void setPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); };
            void setScale(float x, float y, float z) { _scale = glm::vec3(x, y, z); };
            void setRot(float x, float y) { _rotation = glm::vec2(x, y); };
            void setTextureIdx(unsigned int idx) { _textureIdx = (idx < _textures.size() ? idx : 0); };

            glm::vec3 getPosition() { return _position; };
            glm::vec3 getScale() { return _scale; };
            glm::vec2 getRot() { return _rotation; };

        private:
            TextureCache &_texCache;
            glm::vec3 _position;
            glm::vec3 _scale;
            glm::vec2 _rotation;
            unsigned int _textureIdx = 0;
            unsigned int _VAO, _EBO, _VBO;
            std::vector<Vertex> _vertices;
            std::vector<unsigned int> _indices;
            std::vector<Texture> _textures;
    };

    class InpolModel {
        public:
            InpolModel(const std::string modelPath, const std::string nextModelPath, TextureCache &texCache);
            void draw(ShaderProgram &shader, Camera3D &camera);

            void setPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); };
            void setScale(float x, float y, float z) { _scale = glm::vec3(x, y, z); };
            void setRot(float x, float y) { _rotation = glm::vec2(x, y); };
            void setTextureIdx(unsigned int idx) { _textureIdx = (idx < _textures.size() ? idx : 0); }
            void setInpol(float scale) { _inpolScale = scale;
                    if (_inpolScale > 1.0f) { _inpolScale = 1.0f; }
                    if (_inpolScale < 0.0f) { _inpolScale = 0.0f; }};

            glm::vec3 getPosition() { return _position; };
            glm::vec3 getScale() { return _scale; };
            glm::vec2 getRot() { return _rotation; };
            unsigned int getTextureIdx() { return _textureIdx; };
            float getInpolScale() { return _inpolScale; };

        private:
            TextureCache &_texCache;
            glm::vec3 _position;
            glm::vec3 _scale;
            glm::vec2 _rotation;
            float _inpolScale;
            unsigned int _textureIdx;
            unsigned int _VAO, _EBO, _VBO;
            std::vector<InpolVertex> _vertices;
            std::vector<unsigned int> _indices;
            std::vector<Texture> _textures;
            std::string _directory;
            
            std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type);
    };
}
