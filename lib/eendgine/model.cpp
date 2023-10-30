#include "model.hpp"
#include "fatalError.hpp"
#include "shader.hpp"
#include "loadModel.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Eendgine {
    Model::Model(std::string modelPath, TextureCache &texCache): _texCache(texCache) 
    { 
        _position = glm::vec3(0.0f);
        _scale = glm::vec3(1.0f);
        _rotation = glm::vec2(1.0f);
        _textureIdx = 0;
        loadModel(modelPath, _vertices, _indices, _textures, _texCache);

        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);

        glGenBuffers(1, &_VBO);
        glGenBuffers(1, &_EBO);

        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);
        
        glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);
        glad_glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);
        glad_glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        glEnableVertexAttribArray(2);
        glad_glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(3);
    }

    void Model::draw(ShaderProgram &shader, Camera3D &camera){
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
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera.projectionMat[0][0]);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.viewMat[0][0]);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
        
        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);

    }
    InpolModel::InpolModel(std::string modelPath, std::string nextModelPath, TextureCache &texCache): _texCache(texCache) 
    {
        _inpolScale = 0.0f;
        _position = glm::vec3(0.0f);
        _scale = glm::vec3(1.0f);
        _rotation = glm::vec2(0.0f);
        _textureIdx = 0;
        loadModel(modelPath, nextModelPath, _vertices, _indices, _textures, _texCache);
        
        unsigned int tmpSize = _vertices.size();
        unsigned int tmpIdxSize = _indices.size();

        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);

        glGenBuffers(1, &_VBO);
        glGenBuffers(1, &_EBO);

        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(InpolVertex), &_vertices[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);
        
        glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(InpolVertex), (void*)offsetof(InpolVertex, position));
        glEnableVertexAttribArray(0);
        glad_glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(InpolVertex), (void*)offsetof(InpolVertex, nextPosition));
        glEnableVertexAttribArray(1);
        glad_glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(InpolVertex), (void*)offsetof(InpolVertex, color));
        glEnableVertexAttribArray(2);
        glad_glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(InpolVertex), (void*)offsetof(InpolVertex, uv));
        glEnableVertexAttribArray(3);
        glad_glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(InpolVertex), (void*)offsetof(InpolVertex, normal));
        glEnableVertexAttribArray(4);
        glad_glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(InpolVertex), (void*)offsetof(InpolVertex, nextNormal));
        glEnableVertexAttribArray(5); 
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

        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }
}
