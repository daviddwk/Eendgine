#include "entityBatches.hpp"

namespace Eendgine {
void Entities::draw(Shaders& shaders, Camera2D& hudCamera, Camera3D& sceneCamera) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _statues.draw(shaders.getShader(Shader::STATUE), sceneCamera);
    _dolls.draw(shaders.getShader(Shader::DOLL), sceneCamera);
    _boards.draw(shaders.getShader(Shader::BOARD), sceneCamera);

    glClear(GL_DEPTH_BUFFER_BIT);

    _panels.draw(shaders.getShader(Shader::PANEL), hudCamera);
}
} // namespace Eendgine
