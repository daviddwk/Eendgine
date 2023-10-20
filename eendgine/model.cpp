#include <eendgine/model.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

namespace Eendgine {
    Model::Model(std::string path, TextureCache &texCache): _texCache(texCache) 
    {
        _position = glm::vec3(0.0f);
        _scale = glm::vec3(1.0f);
        loadModel(path);
    }

    void Model::draw(ShaderProgram &shader, Camera3D &camera){
        shader.use();

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, _position);
        transform = glm::scale(transform, _scale);

        unsigned int projectionLoc = glGetUniformLocation(shader.programId, "projection");
        unsigned int viewLoc = glGetUniformLocation(shader.programId, "view");
        unsigned int transformLoc = glGetUniformLocation(shader.programId, "transform");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera.projectionMat[0][0]);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.viewMat[0][0]);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

        for (auto &m : _meshes) {
            m.draw(shader, camera);
        }
    }

    void Model::loadModel(std::string path) {
        Assimp::Importer import;
        const aiScene *scene = import.ReadFile(path, 
                aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
            std::cout << "ERROR loadModel" << path << std::endl;
            return;
        }
        _directory = path.substr(0, path.find_last_of('/'));
        processNode(scene->mRootNode, scene);

    }

    void Model::processNode(aiNode *node, const aiScene *scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            _meshes.push_back(processMesh(mesh, scene));
        }
        for(unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }
    
    Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

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
                indices.push_back(face.mIndices[j]);
            }
        }
        
        for (unsigned int i = 0; i < scene->mNumMaterials; i++){
            aiMaterial *material  = scene->mMaterials[i];
            std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            
            // add other map types here whenever
            //
            //std::vector<Texture> opacityMaps = loadMaterialTextures(material, aiTextureType_OPACITY, "opacity");
            //textures.insert(textures.end(), opacityMaps.begin(), opacityMaps.end());
        }
        return Mesh(vertices, indices, textures);
    }

    std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type){
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
