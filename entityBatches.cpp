#include "entityBatches.hpp"

namespace Eendgine {
    
void Entities::construct() {
    assert(_statues == nullptr && _dolls == nullptr && _boards == nullptr && _panels == nullptr);
    _statues = new EntityBatch<Statue>;
    _dolls = new EntityBatch<Doll>;
    _boards = new EntityBatch<Board>;
    _panels = new EntityBatch<Panel>;
}

void Entities::destruct() {
    assert(_statues != nullptr && _dolls != nullptr && _boards != nullptr && _panels != nullptr);
    delete _statues;
    delete _dolls;
    delete _boards;
    delete _panels;
}

EntityBatch<Statue>& Entities::statues() {
    assert(_statues != nullptr);
    return *_statues;
}

EntityBatch<Doll>& Entities::dolls() {
    assert(_dolls != nullptr);
    return *_dolls;
}

EntityBatch<Board>& Entities::boards() {
    assert(_boards != nullptr);
    return *_boards;
}

EntityBatch<Panel>& Entities::panels() {
    assert(_panels != nullptr);
    return *_panels;
}

void Entities::draw(Shaders& shaders, Camera2D& hudCamera, Camera3D& sceneCamera) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _statues->draw(shaders.getShader(Shader::STATUE), sceneCamera);
    _dolls->draw(shaders.getShader(Shader::DOLL), sceneCamera);
    _boards->draw(shaders.getShader(Shader::BOARD), sceneCamera);

    glClear(GL_DEPTH_BUFFER_BIT);

    _panels->draw(shaders.getShader(Shader::PANEL), hudCamera);
}
} // namespace Eendgine
