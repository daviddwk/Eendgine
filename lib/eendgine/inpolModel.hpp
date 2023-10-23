#pragma once

#include "inpolMesh.hpp"
#include "textureCache.hpp"
#include "camera3D.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace Eendgine {
    class InpolModel {
        public:
            InpolModel(std::string modelPath, std::string nextModelPath, TextureCache &texCache);
            void draw(ShaderProgram &shader, Camera3D &camera);

            void setPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); };
            void setScale(float x, float y, float z) { _scale = glm::vec3(x, y, z); };
            void setTextureIdx(unsigned int idx) { _textureIdx = (idx < _textures.size() ? idx : 0); }
            void setInpol(float scale) { _inpolScale = scale;
                    if (_inpolScale > 1.0f) { _inpolScale = 1.0f; }
                    if (_inpolScale < 0.0f) { _inpolScale = 0.0f; }};
            glm::vec3 getPosition() { return _position; };
            glm::vec3 getScale() { return _scale; };
            unsigned int getTextureIdx() { return _textureIdx; };
            float getInpolScale() { return _inpolScale; };
        private:
            TextureCache &_texCache;
            glm::vec3 _position;
            glm::vec3 _scale;
            float _inpolScale = 0.0f;
            unsigned int _textureIdx = 0;

            std::vector<Texture> _textures;
            std::vector<InpolMesh> _meshes;
            //std::vector<InpolMesh> _nextMeshes;
            std::string _directory;

            void loadModel(std::string modelPath, std::string nextModelPath);
            void processNode(aiNode *node, aiNode *nextNode, const aiScene *scene, const aiScene *nextScene);
            InpolMesh processMesh(aiMesh *mesh, aiMesh *nextMesh, const aiScene *scene);
            
            std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type);
    };
}
