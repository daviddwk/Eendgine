#include "shaders.hpp"

namespace Eendgine {

Shaders::Shaders(ShaderProgram panelShader, ShaderProgram boardShader, ShaderProgram statueShader,
    ShaderProgram dollShader, ShaderProgram screenShader)
    : _panelShader(panelShader), _boardShader(boardShader), _statueShader(statueShader),
      _dollShader(dollShader), _screenShader(screenShader) {}

ShaderProgram& Shaders::getShader(Shader shader) {
    switch (shader) {
    default:
    case PANEL:
        return _panelShader;
    case BOARD:
        return _boardShader;
    case STATUE:
        return _statueShader;
    case DOLL:
        return _dollShader;
    case SCREEN:
        return _screenShader;
    }
}

void Shaders::setPixelSize(uint pixelSize) { _screenShader.setInt("pixelSize", pixelSize); }
} // namespace Eendgine
