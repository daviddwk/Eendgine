#include "drawBatches.hpp"

void DrawBatches::draw(Eend::Shaders& shaders, Eend::Camera2D &hudCamera, Eend::Camera3D &sceneCamera) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _models.draw(shaders.getShader(Eend::Shader::model), sceneCamera);
    _animations.draw(shaders.getShader(Eend::Shader::animation), sceneCamera);
    _facingPlanes.draw(shaders.getShader(Eend::Shader::model), sceneCamera);

    glClear(GL_DEPTH_BUFFER_BIT);

    _sprites.draw(shaders.getShader(Eend::Shader::sprite), hudCamera); 
}

void DrawBatches::sort() {
    _models.sort();
    _animations.sort();
    _facingPlanes.sort();
}
