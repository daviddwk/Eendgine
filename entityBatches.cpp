#include "entityBatches.hpp"
#include "primitive.hpp"
#include "shaders.hpp"
#include <GLES3/gl3.h>

namespace Eendgine {

void Entities::construct() {
    Quad::construct();
    assert(
        m_statues == nullptr && m_dolls == nullptr && m_boards == nullptr && m_panels == nullptr);
    m_statues = new EntityBatch<Statue>;
    m_dolls = new EntityBatch<Doll>;
    m_boards = new EntityBatch<Board>;
    m_panels = new EntityBatch<Panel>;
}

void Entities::destruct() {
    Quad::destruct();
    assert(m_statues != nullptr);
    assert(m_dolls != nullptr);
    assert(m_boards != nullptr);
    assert(m_panels != nullptr);
    delete m_statues;
    delete m_dolls;
    delete m_boards;
    delete m_panels;
}

void Entities::shrink() {
    assert(m_statues != nullptr);
    assert(m_dolls != nullptr);
    assert(m_boards != nullptr);
    assert(m_panels != nullptr);
    m_statues->shrink();
    m_dolls->shrink();
    m_boards->shrink();
    m_panels->shrink();
}

EntityBatch<Statue>& Entities::statues() {
    assert(m_statues != nullptr);
    return *m_statues;
}

EntityBatch<Doll>& Entities::dolls() {
    assert(m_dolls != nullptr);
    return *m_dolls;
}

EntityBatch<Board>& Entities::boards() {
    assert(m_boards != nullptr);
    return *m_boards;
}

EntityBatch<Panel>& Entities::panels() {
    assert(m_panels != nullptr);
    return *m_panels;
}

void Entities::draw(Camera2D& hudCamera, Camera3D& sceneCamera) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_statues->draw(Shaders::get().getShader(Shader::statue), sceneCamera);
    m_dolls->draw(Shaders::get().getShader(Shader::doll), sceneCamera);

    glBindVertexArray(Quad::getVao());
    m_boards->draw(Shaders::get().getShader(Shader::board), sceneCamera);
    glBindVertexArray(0);

    glClear(GL_DEPTH_BUFFER_BIT);

    m_panels->draw(Shaders::get().getShader(Shader::panel), hudCamera);
}
} // namespace Eendgine
