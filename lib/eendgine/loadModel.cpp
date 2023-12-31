#include "loadModel.hpp"
#include "fatalError.hpp"


#include <iostream>

namespace Eendgine {
 
    void loadModel(std::string modelPath, std::vector<Vertex> &vertices,
            std::vector<unsigned int> &indices, 
            std::vector<Texture> &textures, TextureCache &texCache) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(modelPath, 
                aiProcess_Triangulate | aiProcess_GenNormals);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
            fatalError("failed to load model");
            return;
        }
        std::string modelDir = modelPath.substr(0, modelPath.find_last_of('/'));
        std::vector<aiMesh*> aiMeshes;
        processNode(scene->mRootNode, scene, aiMeshes);
        unsigned int startIdx = 0;
        for (aiMesh *m : aiMeshes){
            processMesh(m, scene, vertices, indices, startIdx);
            startIdx += m->mNumVertices;
        }
        processTextures(modelDir, scene, textures, texCache);
    }
    
    void loadModel(std::string modelPath, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(modelPath, 
                aiProcess_Triangulate | aiProcess_GenNormals);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
            fatalError("failed to load model");
            return;
        }
        std::string modelDir = modelPath.substr(0, modelPath.find_last_of('/'));
        std::vector<aiMesh*> aiMeshes;
        processNode(scene->mRootNode, scene, aiMeshes);
        unsigned int startIdx = 0;
        for (aiMesh *m : aiMeshes){
            processMesh(m, scene, vertices, indices, startIdx);
            startIdx += m->mNumVertices;
        }
    }

    void loadModel(std::string modelPath, std::string nextModelPath, 
            std::vector<InpolVertex> &vertices, std::vector<unsigned int> &indices,
            std::vector<Texture> &textures, TextureCache &texCache) {
        Assimp::Importer importer;
        Assimp::Importer nextImporter;
        const aiScene *scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_GenNormals);
        const aiScene *nextScene = nextImporter.ReadFile(nextModelPath, aiProcess_Triangulate | aiProcess_GenNormals);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode ||
                !nextScene || nextScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !nextScene->mRootNode) {
            fatalError("failed to load model");
            return;
        }
        // assuming they are in the same directory here
        std::string modelDir = modelPath.substr(0, modelPath.find_last_of('/'));
        std::vector<aiMesh*> aiMeshes;
        std::vector<aiMesh*> nextAiMeshes;
        processNode(scene->mRootNode, scene, aiMeshes);
        processNode(nextScene->mRootNode, nextScene, nextAiMeshes);

        std::vector<Vertex> tmpVertices;
        std::vector<unsigned int> tmpIndices;
        unsigned int startIdx = 0;
        for (aiMesh *m : aiMeshes){
            processMesh(m, scene, tmpVertices, tmpIndices, startIdx);
            startIdx += m->mNumVertices;
        }
        for (int i = 0; i < tmpVertices.size(); i++){
            InpolVertex iv;
            iv.color = tmpVertices[i].color;
            iv.normal = tmpVertices[i].normal;
            iv.position = tmpVertices[i].position;
            iv.uv = tmpVertices[i].uv;
            vertices.push_back(iv);
        }
        tmpVertices.clear();
        tmpIndices.clear();
        startIdx = 0;
        for (aiMesh *m : nextAiMeshes){
            processMesh(m, nextScene, tmpVertices, indices, startIdx);
            startIdx += m->mNumVertices;
        }
        for (int i = 0; i < vertices.size(); i++){
            vertices[i].nextNormal = tmpVertices[i].normal;
            vertices[i].nextPosition = tmpVertices[i].position;
        }
        processTextures(modelDir, scene, textures, texCache);
    }

    void processNode(aiNode *node, const aiScene *scene, std::vector<aiMesh*> &aiMeshes) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMeshes.push_back(scene->mMeshes[node->mMeshes[i]]);
        }
        for(unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene, aiMeshes);
        }
    }
    
    void processMesh(aiMesh *mesh, const aiScene *scene, 
            std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, 
            unsigned int startIdx) {
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            vertex.position = glm::vec3(
                    mesh->mVertices[i].x,
                    mesh->mVertices[i].y,
                    mesh->mVertices[i].z);
            if (mesh->mColors[0]) {
                vertex.color = glm::vec4(
                        mesh->mColors[0][i].r,
                        mesh->mColors[0][i].g,
                        mesh->mColors[0][i].b,
                        1.0f);
            }
            if (mesh->mTextureCoords[0]) {
                vertex.uv = glm::vec2(
                        mesh->mTextureCoords[0][i].x,
                        mesh->mTextureCoords[0][i].y);
            } else {
                vertex.uv = glm::vec2(0.0f, 0.0f);
            }
            if (mesh->HasNormals()){
                vertex.normal = glm::vec3(
                        mesh->mNormals[i].x,
                        mesh->mNormals[i].y,
                        mesh->mNormals[i].z);        
            }
            vertices.push_back(vertex);
        }
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                unsigned int currIdx = face.mIndices[j];
                indices.push_back(face.mIndices[j] + startIdx);
            }
        }
    }

    void processTextures(std::string texDir, const aiScene *scene, 
            std::vector<Texture> &textures, TextureCache &texCache){
        for (unsigned int i = 0; i < scene->mNumMaterials; i++){
            aiMaterial *material  = scene->mMaterials[i];
            for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++) {
                aiString str;
                material->GetTexture(aiTextureType_DIFFUSE, i, &str);
                Texture texture = texCache.getTexture(texDir + '/' + (std::string)str.C_Str());
                textures.push_back(texture);
            }
        }
    }
}
