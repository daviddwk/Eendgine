#include "shaders.hpp"

namespace Eendgine {

Shaders::Shaders(
    ShaderProgram panelShader, ShaderProgram boardShader, ShaderProgram statueShader,
    ShaderProgram dollShader, ShaderProgram screenShader)
    : m_panelShader(panelShader), m_boardShader(boardShader), m_statueShader(statueShader),
      m_dollShader(dollShader), m_screenShader(screenShader) {}

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

void Shaders::setPixelSize(uint pixelSize) { m_screenShader.setInt("pixelSize", pixelSize); }
} // namespace Eendgine
