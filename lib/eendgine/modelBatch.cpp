#include "modelBatch.hpp"
#include <algorithm>


namespace Eendgine {

    ModelBatch::ModelBatch(){
    }

    void ModelBatch::insertModel(Model* model) {
        _models.insert(model);
    }

    void ModelBatch::eraseModel(Model* model) {
        _models.erase(model);
    }

    void ModelBatch::draw(ShaderProgram &shader, Camera3D &camera) {
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
            model->draw(shader, camera, false);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}
