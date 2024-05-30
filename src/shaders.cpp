#include "shaders.hpp" 

namespace Eend = Eendgine;

Shaders::Shaders(Eend::ShaderProgram spriteShader,
        Eend::ShaderProgram modelShader,
        Eend::ShaderProgram animationShader,
        Eend::ShaderProgram screenShader) :
        _spriteShader(spriteShader),
        _modelShader(modelShader),
        _animationShader(animationShader),
        _screenShader(screenShader)
{

}

Eend::ShaderProgram& Shaders::getShader(Shader shader) {
    switch (shader) {
        default:
        case sprite:
            return _spriteShader;
            break;
        case model:
            return _modelShader;
            break;
        case animation:
            return _animationShader;
            break;
        case screen:
            return _screenShader;
            break;
    }
}

void Shaders::setPixelSize(uint pixelSize) {
    _screenShader.setInt("pixelSize", pixelSize);
}
