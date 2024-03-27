#include "renderBatch.hpp"
#include <algorithm>

namespace Eendgine {
    void renderModelBatch(std::vector<Model*>* models, ShaderProgram &shader, Camera3D &camera) {
        std::sort(models->begin(), models->end(), [](Model* a, Model* b)
                {
                    return a->getTexture() > b->getTexture();
                });
        glActiveTexture(GL_TEXTURE0);
        std::string texName = "texture_diffuse";
        glUniform1i(glGetUniformLocation(shader.getProgramID(), texName.c_str()), 0);
        unsigned int lastTexture = 0;
        unsigned int thisTexture = 0; 
        for (int i = 0; i < models->size(); i++) {
            thisTexture = (*models)[i]->getTexture(); 
            if (i == 0 || lastTexture != thisTexture) {
                glBindTexture(GL_TEXTURE_2D, thisTexture);
            }
            lastTexture = thisTexture;
            (*models)[i]->draw(shader, camera, false);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
