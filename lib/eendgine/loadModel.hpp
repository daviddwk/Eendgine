#pragma once
#include "vertex.hpp"
#include "textureCache.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>

namespace Eendgine {
    void loadModel(std::string modelPath, 
            std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, 
            std::vector<Texture> &textures, TextureCache &texCache);
    void loadModel(std::string modelPath, 
            std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
    void loadModel(std::string modelPath, std::string nextModelPath, 
            std::vector<InpolVertex> &vertices, std::vector<unsigned int> &indices, 
            std::vector<Texture> &textures, TextureCache &texCache);
    void processNode(aiNode *node, const aiScene *scene, std::vector<aiMesh*> &aiMeshes);
    void processMesh(aiMesh *mesh, const aiScene *scene, 
            std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, 
            unsigned int startIdx);
    void processTextures(std::string texDir, const aiScene *scene, 
            std::vector<Texture> &textures, TextureCache &texCache);
}
