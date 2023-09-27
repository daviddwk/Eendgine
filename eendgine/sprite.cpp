#include "eendgine/sprite.hpp"
#include <eendgine/textureCache.hpp>

namespace Eendgine {

    void Sprite::update(Texture texture) {
        float verticies[32] = {
            // positions                            // colors           // texture coords
            x - (w / 2.0f), y - (h / 2.0f), 0.0f,   0.0f, 0.0f, 1.0f,   0.0, 0.0, // bottom left
            x - (w / 2.0f), y + (h / 2.0f), 0.0f,   0.0f, 1.0f, 0.0f,   0.0, 1.0, // top left 
            x + (w / 2.0f), y + (h / 2.0f), 0.0f,   1.0f, 0.0f, 0.0f,   1.0, 1.0, // top right
            x + (w / 2.0f), y - (h / 2.0f), 0.0f,   0.0f, 1.0f, 1.0f,   1.0, 0.0  // bottom right
        };

        for (int i = 0; i < 32; i++) {
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
        
        glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glad_glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glad_glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        _texture = texture;
    } 

    void Sprite::render(Eendgine::Shader *shader) {
        shader->use();
        glBindTexture(GL_TEXTURE_2D, _texture.id);
        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

}
