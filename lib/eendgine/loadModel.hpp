#pragma once
#include "mesh.hpp"
#include "textureCache.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>

namespace Eendgine {
    void loadModel(std::string modelPath, std::vector<Mesh> &meshes, std::vector<Texture> &textures, TextureCache &texCache);
    void processNode(aiNode *node, const aiScene *scene, std::vector<aiMesh*> &aiMeshes);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    void processTextures(std::string texDir, const aiScene *scene, std::vector<Texture> &textures, TextureCache &texCache);
}
