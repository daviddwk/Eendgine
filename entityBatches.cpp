#include "entityBatches.hpp"

namespace Eendgine {
void Entities::draw(Shaders& shaders, Camera2D& hudCamera, Camera3D& sceneCamera) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _statues.draw(shaders.getShader(Shader::model), sceneCamera);
    _dolls.draw(shaders.getShader(Shader::animation), sceneCamera);
    _boards.draw(shaders.getShader(Shader::model), sceneCamera);

    glClear(GL_DEPTH_BUFFER_BIT);

    _panels.draw(shaders.getShader(Shader::sprite), hudCamera);
}
} // namespace Eendgine
