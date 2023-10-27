#include "inpolModel.hpp"
#include "fatalError.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Eendgine {
    InpolModel::InpolModel(std::string modelPath, std::string nextModelPath, TextureCache &texCache): _texCache(texCache) 
    {
        _inpolScale = 0.0f;
        _position = glm::vec3(0.0f);
        _scale = glm::vec3(1.0f);
        _rotation = glm::vec2(0.0f);
        _textureIdx = 0;
        loadModel(modelPath, nextModelPath);
    }

    void InpolModel::draw(ShaderProgram &shader, Camera3D &camera){
        shader.use();

        // using RGB(1,0,1) for transparent
        // parts of the texture using shaders
        glActiveTexture(GL_TEXTURE0);
        std::string texName = "texture_diffuse";
        glUniform1i(glGetUniformLocation(shader.programId, texName.c_str()), 0);
        glBindTexture(GL_TEXTURE_2D, _textures[_textureIdx].id);
        
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, _position);
        transform = glm::rotate(transform, glm::radians(-_rotation.x), glm::vec3( 0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(-_rotation.y), glm::vec3(-1.0f, 0.0f, 0.0f));
        transform = glm::scale(transform, _scale);

        unsigned int projectionLoc = glGetUniformLocation(shader.programId, "projection");
        unsigned int viewLoc = glGetUniformLocation(shader.programId, "view");
        unsigned int transformLoc = glGetUniformLocation(shader.programId, "transform");
        unsigned int inpolLoc = glGetUniformLocation(shader.programId, "inpol");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera.projectionMat[0][0]);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.viewMat[0][0]);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
        glUniform1f(inpolLoc, _inpolScale);

        for (auto &m : _meshes) {
            m.draw();
        }
    }

    void InpolModel::loadModel(std::string modelPath, std::string nextModelPath) {
        Assimp::Importer importer;
        Assimp::Importer nextImport;
        const aiScene *scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_GenNormals);
        const aiScene *nextScene = nextImport.ReadFile(nextModelPath, aiProcess_Triangulate | aiProcess_GenNormals);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
            fatalError("failed to load model");
            return;
        } else if (!nextScene || nextScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !nextScene->mRootNode) {
            fatalError("failed to load model");
        }
        // for now assume that both are in the same directory
        _directory = modelPath.substr(0, modelPath.find_last_of('/'));
        processNode(scene->mRootNode, nextScene->mRootNode, scene, nextScene);
    }

    void InpolModel::processNode(aiNode *node, aiNode *nextNode, const aiScene *scene, const aiScene *nextScene) {
        // add error checking to make sure mNumMeshes is the same
        // among other things
        if (node->mNumMeshes != nextNode->mNumMeshes) {
            fatalError("model NumMeshes mismatch");
        }
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            aiMesh *nextMesh = nextScene->mMeshes[nextNode->mMeshes[i]]; 
            _meshes.push_back(processMesh(mesh, nextMesh, scene));
        }
        if (node->mNumChildren != nextNode->mNumChildren) {
            fatalError("model NumChildren mismatch");
        }
        for(unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], nextNode->mChildren[i], scene, nextScene);
        }
    }
    
    InpolMesh InpolModel::processMesh(aiMesh *mesh, aiMesh *nextMesh, const aiScene *scene) {
        std::vector<InpolVertex> vertices;
        std::vector<unsigned int> indices;
        
        if (mesh->mNumVertices != nextMesh->mNumVertices) {
            fatalError("mesh NumVertices mismatch");
        } else if (mesh->HasNormals() != nextMesh->HasNormals()) {
            fatalError("mesh HasNormals mismatch");
        }
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            InpolVertex vertex;
            vertex.position = glm::vec3(
                    mesh->mVertices[i].x,
                    mesh->mVertices[i].y,
                    mesh->mVertices[i].z);
            vertex.nextPosition = glm::vec3(
                    nextMesh->mVertices[i].x,
                    nextMesh->mVertices[i].y,
                    nextMesh->mVertices[i].z);
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
                vertex.nextNormal = glm::vec3(
                        nextMesh->mNormals[i].x,
                        nextMesh->mNormals[i].y,
                        nextMesh->mNormals[i].z);        
            }
            vertices.push_back(vertex);
        }
        
        if (mesh->mNumFaces != nextMesh->mNumFaces) {
            fatalError("mesh NumFaces mismatch");
        }
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            if (face.mNumIndices != nextMesh->mFaces[i].mNumIndices) {
                fatalError("mesh NumFaces mismatch");
            }
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }
        
        for (unsigned int i = 0; i < scene->mNumMaterials; i++){
            aiMaterial *material  = scene->mMaterials[i];
            std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
            _textures.insert(_textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            
            // add other map types here whenever
            //
            //std::vector<Texture> opacityMaps = loadMaterialTextures(material, aiTextureType_OPACITY, "opacity");
            //textures.insert(textures.end(), opacityMaps.begin(), opacityMaps.end());
        }
        return InpolMesh(vertices, indices, _textures);
    }

    std::vector<Texture> InpolModel::loadMaterialTextures(aiMaterial *mat, aiTextureType type){
        std::vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);
            Texture texture = _texCache.getTexture(_directory + '/' + (std::string)str.C_Str());
            textures.push_back(texture);
        }
        return textures;
    }

}
