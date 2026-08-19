#pragma once

#include "shader.hpp"

namespace Eendgine {

const std::string SHADER_PATH_PANEL_VERT = "shaders/panel.vert";
const std::string SHADER_PATH_PANEL_FRAG = "shaders/panel.frag";
const std::string SHADER_PATH_BOARD_VERT = "shaders/board.vert";
const std::string SHADER_PATH_BOARD_FRAG = "shaders/board.frag";
const std::string SHADER_PATH_STATUE_VERT = "shaders/statue.vert";
const std::string SHADER_PATH_STATUE_FRAG = "shaders/statue.frag";
const std::string SHADER_PATH_DOLL_VERT = "shaders/doll.vert";
const std::string SHADER_PATH_DOLL_FRAG = "shaders/doll.frag";
const std::string SHADER_PATH_SCREEN_VERT = "shaders/screen.vert";
const std::string SHADER_PATH_SCREEN_FRAG = "shaders/screen.frag";

const std::string SHADER_SCREEN_INT_PIXEL_SIZE = "pixelSize";

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
