#include <eendgine/mesh.hpp>
#include <string>
#include <glm/glm.hpp>

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

    void Mesh::draw(ShaderProgram &shader) {
        //shader.use();
        // first texture is treated as diffure
        // second is treated as opacity texture
        // feels dirty, but is easy to expand later
        for(unsigned int i = 0; i < _textures.size() && i < 2; i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            std::string texType = (i == 0 ? "diffuse" : "opacity");
            std::string texName = "texture_" + texType;
            glUniform1i(glGetUniformLocation(shader.programId, texName.c_str()), i);
            glBindTexture(GL_TEXTURE_2D, _textures[i].id);
        }
        

        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }
}
