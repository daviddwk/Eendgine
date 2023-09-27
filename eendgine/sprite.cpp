#include "eendgine/sprite.hpp"

namespace Eendgine {

    void Sprite::update() {
        float verticies[12] = {
            x - (w / 2.0f), y - (h / 2.0f), 0.0f,
            x - (w / 2.0f), y + (h / 2.0f), 0.0f,
            x + (w / 2.0f), y + (h / 2.0f), 0.0f,
            x + (w / 2.0f), y - (h / 2.0f), 0.0f 
        };

        for (int i = 0; i < 12; i++) {
            _verticies[i] = verticies[i];
        }

        int indicies[6] = {
            0, 1, 2,
            0, 2, 3
        };

        for (int i = 0; i < 6; i++) {
            _indicies[i] = indicies[i];
        }

        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);

        unsigned int VBO;
        glGenBuffers(1, &VBO);

        unsigned int EBO;
        glGenBuffers(1, &EBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), _verticies, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), _indicies, GL_STATIC_DRAW);
        
        glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    } 

    void Sprite::render(Eendgine::ShaderProgram *shader) {
        shader->use();
        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}
