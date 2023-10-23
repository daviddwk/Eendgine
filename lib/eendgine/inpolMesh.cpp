#include "inpolMesh.hpp"
#include <string>
#include <glm/glm.hpp>

namespace Eendgine {

    InpolMesh::InpolMesh(std::vector<InpolVertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
        _vertices = vertices;
        _indices = indices;
        setup();
    }

    void InpolMesh::setup() {
        
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

    void InpolMesh::draw(ShaderProgram &shader) { 

        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }
}
