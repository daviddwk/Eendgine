#include "shaders.hpp"

namespace Eendgine {

Shaders::Shaders(ShaderProgram panelShader, ShaderProgram boardShader, ShaderProgram statueShader,
    ShaderProgram dollShader, ShaderProgram screenShader)
    : _panelShader(panelShader), _boardShader(boardShader), _statueShader(statueShader),
      _dollShader(dollShader), _screenShader(screenShader) {}

ShaderProgram& Shaders::getShader(Shader shader) {
    switch (shader) {
    default:
    case panel:
        return _panelShader;
    case board:
        return _boardShader;
    case statue:
        return _statueShader;
    case doll:
        return _dollShader;
    case screen:
        return _screenShader;
    }
}

void Shaders::setPixelSize(uint pixelSize) { _screenShader.setInt("pixelSize", pixelSize); }
} // namespace Eendgine
