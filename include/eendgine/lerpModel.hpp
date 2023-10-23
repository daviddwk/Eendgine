#pragma once

#include <eendgine/lerpMesh.hpp>
#include <eendgine/textureCache.hpp>
#include <eendgine/camera3D.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace Eendgine {
    class LerpModel {
        public:
            LerpModel(std::string modelPath, std::string nextModelPath, TextureCache &texCache);
            void draw(ShaderProgram &shader, Camera3D &camera);

            void setPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); };
            void setScale(float x, float y, float z) { _scale = glm::vec3(x, y, z); };
            void setTextureIdx(unsigned int idx) { _textureIdx = (idx < _textures.size() ? idx : 0); }

            glm::vec3 getPosition() { return _position; };
            glm::vec3 getScale() {return _scale; };
        private:
            TextureCache &_texCache;
            glm::vec3 _position;
            glm::vec3 _scale;
            float lerp = 0.0f;
            unsigned int _textureIdx = 0;

            std::vector<Texture> _textures;
            std::vector<LerpMesh> _meshes;
            //std::vector<LerpMesh> _nextMeshes;
            std::string _directory;

            void loadModel(std::string modelPath, std::string nextModelPath);
            void processNode(aiNode *node, aiNode *nextNode, const aiScene *scene, const aiScene *nextScene);
            LerpMesh processMesh(aiMesh *mesh, aiMesh *nextMesh, const aiScene *scene);
            
            std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type);
    };
}
