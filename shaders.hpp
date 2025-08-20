#pragma once

#include "shader.hpp"

namespace Eendgine {
enum Shader { PANEL, BOARD, STATUE, DOLL, SCREEN };
class Shaders {
    public:
        Shaders(ShaderProgram panelShader, ShaderProgram boardShader, ShaderProgram statueShader,
            ShaderProgram dollShader, ShaderProgram screenShader);
        ShaderProgram& getShader(Shader shader);
        void setPixelSize(uint pixelSize);

    private:
        ShaderProgram m_panelShader;
        ShaderProgram m_boardShader;
        ShaderProgram m_statueShader;
        ShaderProgram m_dollShader;
        ShaderProgram m_screenShader;
};
} // namespace Eendgine
