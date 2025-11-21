#pragma once
#include <GLES3/gl3.h>
#include <iostream>

namespace Eendgine {

class ShaderProgram {
    public:
        ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
        void use();
        GLuint getProgramID() { return m_programID; };
        void setInt(std::string name, int value) {
            glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
        }

    private:
        void compileShader(GLuint id, std::string shaderPath);
        GLuint m_programID;
        GLuint m_vertexShaderID;
        GLuint m_fragmentShaderID;
};
} // namespace Eendgine
