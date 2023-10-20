#pragma once

#include <eendgine/mesh.hpp>
#include <eendgine/textureCache.hpp>
#include <eendgine/camera3D.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

namespace Eendgine {
    class Model {
        public:
            Model(std::string path, TextureCache &texCache);
            void draw(ShaderProgram &shader, Camera3D &camera);
        private:
            std::vector<Mesh> _meshes;
            std::string _directory;
            TextureCache &_texCache;

            void loadModel(std::string path);
            void processNode(aiNode *node, const aiScene *scene);
            Mesh processMesh(aiMesh *mesh, const aiScene *scene);
            
            std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type);
    };
}
