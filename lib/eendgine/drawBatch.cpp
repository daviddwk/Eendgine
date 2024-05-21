#include "drawBatch.hpp"
#include <algorithm>


namespace Eendgine {
    SpriteBatch::SpriteBatch(){
    }

    void SpriteBatch::insertSprite(Sprite* sprite) {
        _sprites.insert(sprite);
    }

    void SpriteBatch::eraseSprite(Sprite* sprite) {
        _sprites.erase(sprite);
    }

    void SpriteBatch::draw(ShaderProgram &shader, Camera3D &camera) {
        glActiveTexture(GL_TEXTURE0);
        std::string texName = "texture_diffuse";
        glUniform1i(glGetUniformLocation(shader.getProgramID(), texName.c_str()), 0);
        unsigned int lastTexture = 0;
        unsigned int thisTexture = 0; 
        for (auto sprite : _sprites) {
            thisTexture = sprite->getTexture(); 
            if (lastTexture != thisTexture) {
                glBindTexture(GL_TEXTURE_2D, thisTexture);
            }
            lastTexture = thisTexture;
            sprite->draw(shader, false);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void SpriteBatch::draw(ShaderProgram &shader, Camera2D &camera) {
        glActiveTexture(GL_TEXTURE0);
        std::string texName = "texture_diffuse";
        glUniform1i(glGetUniformLocation(shader.getProgramID(), texName.c_str()), 0);
        unsigned int lastTexture = 0;
        unsigned int thisTexture = 0; 
        for (auto sprite : _sprites) {
            thisTexture = sprite->getTexture(); 
            if (lastTexture != thisTexture) {
                glBindTexture(GL_TEXTURE_2D, thisTexture);
            }
            lastTexture = thisTexture;
            sprite->draw(shader, false);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    

}
