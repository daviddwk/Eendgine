#pragma once

#include "shader.hpp"

namespace Eendgine {
enum Shader { panel, board, statue, doll, screen };
class Shaders {
    public:
        Shaders(ShaderProgram panelShader, ShaderProgram boardShader, ShaderProgram statueShader,
            ShaderProgram dollShader, ShaderProgram screenShader);
        ShaderProgram& getShader(Shader shader);
        void setPixelSize(uint pixelSize);

    private:
        ShaderProgram _panelShader;
        ShaderProgram _boardShader;
        ShaderProgram _statueShader;
        ShaderProgram _dollShader;
        ShaderProgram _screenShader;
};
} // namespace Eendgine
