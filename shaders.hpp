#pragma once

#include "shader.hpp"

namespace Eendgine {
enum Shader { sprite, model, animation, screen };
class Shaders {
    public:
        Shaders(ShaderProgram spriteShader, ShaderProgram modelShader,
            ShaderProgram animationShader, ShaderProgram screenShader);
        ShaderProgram& getShader(Shader shader);
        void setPixelSize(uint pixelSize);

    private:
        ShaderProgram _spriteShader;
        ShaderProgram _modelShader;
        ShaderProgram _animationShader;
        ShaderProgram _screenShader;
};
} // namespace Eendgine
