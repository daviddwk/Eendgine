#pragma once

#include <eendgine/mesh.hpp>
#include <eendgine/textureCache.hpp>
#include <eendgine/camera3D.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace Eendgine {
    class Model {
        public:
            Model(std::string path, TextureCache &texCache);
            void draw(ShaderProgram &shader, Camera3D &camera);

            void setPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); };
            void setScale(float x, float y, float z) { _scale = glm::vec3(x, y, z); };
            
            // pull out textures into the model class, not per mesh, and then make this
            // not stupid
            void setTextureIdx(unsigned int idx) {
                for (auto &m : _meshes){
                    m.setTextureIdx(idx);
                }
            }

            glm::vec3 getPosition() { return _position; };
            glm::vec3 getScale() {return _scale; };
        private:
            TextureCache &_texCache;
            glm::vec3 _position;
            glm::vec3 _scale;

            std::vector<Mesh> _meshes;
            std::string _directory;

            void loadModel(std::string path);
            void processNode(aiNode *node, const aiScene *scene);
            Mesh processMesh(aiMesh *mesh, const aiScene *scene);
            
            std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type);
    };
}
