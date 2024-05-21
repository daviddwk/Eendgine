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
            sprite->draw(shader, camera, false);
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
            sprite->draw(shader, camera, false);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    ModelBatch::ModelBatch(){
    }

    void ModelBatch::insertModel(Model* model) {
        _models.insert(model);
    }

    void ModelBatch::eraseModel(Model* model) {
        _models.erase(model);
    }

    void ModelBatch::draw(ShaderProgram &shader) {
        glActiveTexture(GL_TEXTURE0);
        std::string texName = "texture_diffuse";
        glUniform1i(glGetUniformLocation(shader.getProgramID(), texName.c_str()), 0);
        unsigned int lastTexture = 0;
        unsigned int thisTexture = 0; 
        for (auto model : _models) {
            thisTexture = model->getTexture(); 
            if (lastTexture != thisTexture) {
                glBindTexture(GL_TEXTURE_2D, thisTexture);
            }
            lastTexture = thisTexture;
            model->draw(shader, false);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}
