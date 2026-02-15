#include "assert.h"
#include "shaders.hpp"

namespace Eendgine {

void Shaders::construct(
    ShaderProgram panelShader, ShaderProgram boardShader, ShaderProgram statueShader,
    ShaderProgram dollShader, ShaderProgram screenShader) {

    assert(m_instance == nullptr);
    m_instance = new Shaders(panelShader, boardShader, statueShader, dollShader, screenShader);
}

void Shaders::destruct() {
    assert(m_instance != nullptr);
    delete m_instance;
    m_instance = nullptr;
}

Shaders& Shaders::get() {
    assert(m_instance != nullptr);
    return *m_instance;
}

Shaders::Shaders(
    ShaderProgram panelShader, ShaderProgram boardShader, ShaderProgram statueShader,
    ShaderProgram dollShader, ShaderProgram screenShader)
    : m_panelShader(panelShader), m_boardShader(boardShader), m_statueShader(statueShader),
      m_dollShader(dollShader), m_screenShader(screenShader) {}

Shaders::~Shaders() {}

ShaderProgram& Shaders::getShader(Shader shader) {
    switch (shader) {
    default:
    case Shader::panel:
        return m_panelShader;
    case Shader::board:
        return m_boardShader;
    case Shader::statue:
        return m_statueShader;
    case Shader::doll:
        return m_dollShader;
    case Shader::screen:
        return m_screenShader;
    }
}
} // namespace Eendgine
