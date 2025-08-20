#pragma once
#include <GLES3/gl3.h>
#include <iostream>

namespace Eendgine {

class ShaderProgram {
    public:
        ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
        void use();
        unsigned int getProgramID() { return m_programID; };
        void setInt(std::string name, int value) {
            glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
        }

    private:
        void compileShader(unsigned int id, std::string shaderPath);
        unsigned int m_programID;
        unsigned int m_vertexShaderID;
        unsigned int m_fragmentShaderID;
};
} // namespace Eendgine
