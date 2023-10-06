#include "eendgine/sprite.hpp"
#include <eendgine/textureCache.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Eendgine {
    
    void Sprite::init(float xPos, float yPos, float zPos, float width, float height, Texture texture) {
        std::vector<Texture> textures;
        textures.push_back(texture);
        init(xPos, yPos, zPos, width, height, textures);
    }
    
    void Sprite::init(float xPos, float yPos, float zPos, float width, float height, std::vector<Texture> textures) {

        x = xPos;
        y = yPos;
        z = zPos;
        w = width;
        h = height;
        scale = 1;
        rotation = 0;


        _textures = textures;
        _currentTexture = &_textures[0];
        
        Vertex verticies[4];
        
        verticies[0].setPosition( (w / 2.0f),  (h / 2.0f), 0.0f);
        verticies[1].setPosition( (w / 2.0f), -(h / 2.0f), 0.0f);
        verticies[2].setPosition(-(w / 2.0f), -(h / 2.0f), 0.0f);
        verticies[3].setPosition(-(w / 2.0f),  (h / 2.0f), 0.0f);

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
        
        glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glad_glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glad_glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }  

    void Sprite::setTexture(std::vector<Texture>::size_type textureIndex){
        _currentTexture = &_textures[textureIndex];
    }

    std::vector<Texture>::size_type Sprite::getNumTextures(){
        return _textures.size();
    }

    void Sprite::render(Eendgine::ShaderProgram *shader, Eendgine::Camera2D *camera) {
        glBindTexture(GL_TEXTURE_2D, _currentTexture->id);
        
        glm::mat4 trans = camera->getCameraMatrix(); //glm::mat4(1.0f);
        
        trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
        trans = glm::rotate(trans, glm::radians(-rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(scale, scale, scale));
        

        unsigned int transformLoc = glGetUniformLocation(shader->programId, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        
        shader->use();

        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

}
