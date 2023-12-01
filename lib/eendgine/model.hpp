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
            Model();
            virtual void draw(ShaderProgram &shader, Camera3D &camera);
            
            void setPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); };
            void setScale(float x, float y, float z) { _scale = glm::vec3(x, y, z); };
            void setRot(float x, float y) { _rotation = glm::vec2(x, y); };

            glm::vec3 getPosition() { return _position; };
            glm::vec3 getScale() { return _scale; };
            glm::vec2 getRot() { return _rotation; };
        protected:
            glm::vec3 _position;
            glm::vec3 _scale;
            glm::vec2 _rotation;
    };
    
    class StaticModel : public Model {
        public:
            StaticModel(std::string modelPath, TextureCache &texCache);
            void draw(ShaderProgram &shader, Camera3D &camera);

            void setTextureIdx(unsigned int idx) { _textureIdx = (idx < _textures.size() ? idx : 0); };

            unsigned int getTextureIdx() { return _textureIdx; };
        private:
            TextureCache &_texCache;
            unsigned int _textureIdx;
            std::vector<Texture> _textures;

            unsigned int _VAO, _EBO, _VBO;
            std::vector<Vertex> _vertices;
            std::vector<unsigned int> _indices;
            
    };

    class AnimatedModel : public Model {
        public:
            AnimatedModel(std::vector<std::string> modelPaths, TextureCache &texCache);
            AnimatedModel(const std::string modelPath, const std::string nextModelPath, TextureCache &texCache);
            void draw(ShaderProgram &shader, Camera3D &camera);
            
            void setTextureIdx(unsigned int idx) { _textureIdx = (idx < _textures.size() ? idx : 0); };
            void setAnim(float scale) { _animScale = scale - (int) scale; };

            unsigned int getTextureIdx() { return _textureIdx; };
            float getAnim() { return _animScale; };

        private:
            float _animScale;

            TextureCache &_texCache;
            unsigned int _textureIdx;
            std::vector<Texture> _textures;

            std::vector<unsigned int> _VAOs, _EBOs, _VBOs;
            std::vector<std::vector<InpolVertex>> _vertices;
            std::vector<std::vector<unsigned int>> _indices;
    };
}
