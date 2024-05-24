#include "drawBatches.hpp"

void DrawBatches::draw(Shaders& shaders) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _models.draw(shaders.getShader(Shader::model));
    _animations.draw(shaders.getShader(Shader::animation));
    _facingPlanes.draw(shaders.getShader(Shader::model));

    glClear(GL_DEPTH_BUFFER_BIT);

    _sprites.draw(shaders.getShader(Shader::sprite)); 
}
