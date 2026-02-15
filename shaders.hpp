#pragma once

#include "shader.hpp"

namespace Eendgine {
enum class Shader { panel, board, statue, doll, screen };
class Shaders {
    public:
        static void construct(
            ShaderProgram panelShader, ShaderProgram boardShader, ShaderProgram statueShader,
            ShaderProgram dollShader, ShaderProgram screenShader);
        static void destruct();
        static Shaders& get();

        ShaderProgram& getShader(Shader shader);

    private:
        Shaders(
            ShaderProgram panelShader, ShaderProgram boardShader, ShaderProgram statueShader,
            ShaderProgram dollShader, ShaderProgram screenShader);
        ~Shaders();

        Shaders(const Shaders&) = delete;
        Shaders& operator=(const Shaders&) = delete;

        Shaders(Shaders&& other) = delete;
        Shaders& operator=(Shaders&& other) = delete;

        inline static Shaders* m_instance = nullptr;

        ShaderProgram m_panelShader;
        ShaderProgram m_boardShader;
        ShaderProgram m_statueShader;
        ShaderProgram m_dollShader;
        ShaderProgram m_screenShader;
};
} // namespace Eendgine
