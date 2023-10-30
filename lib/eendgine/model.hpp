#pragma once
#include "mesh.hpp"
#include "textureCache.hpp"
#include "camera3D.hpp"
#include "shader.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace Eendgine {
    void loadModel(std::string modelPath, std::vector<Mesh> &meshes, std::vector<Texture> &textures, TextureCache &texCache);
    void processNode(aiNode *node, const aiScene *scene, std::vector<aiMesh*> &aiMeshes);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    void processTextures(std::string texDir, const aiScene *scene, std::vector<Texture> &textures, TextureCache &texCache);

    class Model {
        public:
            Model(std::string path, TextureCache &texCache);
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

            std::vector<Texture> _textures;
            std::vector<Mesh> _meshes;

            
    };

}
