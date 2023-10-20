#include "eendgine/sprite.hpp"
#include <eendgine/textureCache.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Eendgine {
    
    Sprite::Sprite(float xPos, float yPos, float width, float height, Texture texture) {
        std::vector<Texture> textures;
        textures.push_back(texture);
        setup(xPos, yPos, width, height, textures);
    }

    Sprite::Sprite(float xPos, float yPos, float width, float height, std::vector<Texture> textures) {
        setup(xPos, yPos, width, height, textures);
    }
    
    void Sprite::setup(float xPos, float yPos, float width, float height, std::vector<Texture> textures) {

        _position = glm::vec3(xPos, yPos, 0.0f);
        _size = glm::vec3(width, height, 1.0f);
        _rotation = 0;

        _textures = textures;
        _textureIdx = 0;
        
        Vertex verticies[4];
        
        // centered on origin
        // with width and height of 1
        verticies[0].setPosition( 0.5f, 0.5f, 0.0f);
        verticies[1].setPosition( 0.5f,-0.5f, 0.0f);
        verticies[2].setPosition(-0.5f,-0.5f, 0.0f);
        verticies[3].setPosition(-0.5f, 0.5f, 0.0f);

        verticies[0].setColor(0.0f, 0.0f, 1.0f, 1.0f);
        verticies[1].setColor(0.0f, 1.0f, 0.0f, 1.0f);
        verticies[2].setColor(1.0f, 0.0f, 0.0f, 1.0f);
        verticies[3].setColor(0.0f, 1.0f, 1.0f, 1.0f);
        
        verticies[0].setUv(1.0f, 1.0f);
        verticies[1].setUv(1.0f, 0.0f);
        verticies[2].setUv(0.0f, 0.0f);
        verticies[3].setUv(0.0f, 1.0f);
        
        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
        };

        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);

        unsigned int VBO;
        glGenBuffers(1, &VBO);

        unsigned int EBO;
        glGenBuffers(1, &EBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glad_glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glad_glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(7 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glad_glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(9 * sizeof(float)));
        glEnableVertexAttribArray(3);
    }  

    std::vector<Texture>::size_type Sprite::getNumTextures(){
        return _textures.size();
    }

    void Sprite::draw(Eendgine::ShaderProgram &shader, Eendgine::Camera2D &camera) {
        shader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _textures[_textureIdx].id);
        
        glm::mat4 trans = camera.getCameraMatrix(); //glm::mat4(1.0f);
        
        trans = glm::translate(trans, _position);
        trans = glm::rotate(trans, glm::radians(-_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, _size);

        unsigned int transformLoc = glGetUniformLocation(shader.programId, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}
