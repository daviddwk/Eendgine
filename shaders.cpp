#include "shaders.hpp"

namespace Eendgine {

Shaders::Shaders(ShaderProgram panelShader, ShaderProgram boardShader, ShaderProgram statueShader,
    ShaderProgram dollShader, ShaderProgram screenShader)
    : m_panelShader(panelShader), m_boardShader(boardShader), m_statueShader(statueShader),
      m_dollShader(dollShader), m_screenShader(screenShader) {}

ShaderProgram& Shaders::getShader(Shader shader) {
    switch (shader) {
    default:
    case PANEL:
        return m_panelShader;
    case BOARD:
        return m_boardShader;
    case STATUE:
        return m_statueShader;
    case DOLL:
        return m_dollShader;
    case SCREEN:
        return m_screenShader;
    }
}

void Shaders::setPixelSize(uint pixelSize) { m_screenShader.setInt("pixelSize", pixelSize); }
} // namespace Eendgine
