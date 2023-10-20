#include <eendgine/mesh.hpp>
#include <string>

namespace Eendgine {

    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
        _vertices = vertices;
        _indices = indices;
        _textures = textures;

        setup();
    }

    void Mesh::setup() {
        
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

    void Mesh::draw(ShaderProgram *shader, Camera3D *camera) {
        shader->use();
        for(int i = 0; i < _textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            std::string texName = "texture_" + _textures[i].type + std::to_string(i);
            std::cout << texName << std::endl;
            glUniform1i(glGetUniformLocation(shader->programId, texName.c_str()), i);
            glBindTexture(GL_TEXTURE_2D, _textures[i].id);
        }
        
        unsigned int projectionLoc = glGetUniformLocation(shader->programId, "projection");
        unsigned int viewLoc = glGetUniformLocation(shader->programId, "view");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera->projectionMat[0][0]);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera->viewMat[0][0]);

        //glm::mat4 trans = camera->getCameraMatrix(); //glm::mat4(1.0f);
        
        //trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
        //trans = glm::rotate(trans, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        //trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f));
        
        //unsigned int transformLoc = glGetUniformLocation(shader->programId, "transform");
        //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        
        
        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }
}
