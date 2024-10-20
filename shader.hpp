#pragma once
#include <GLES3/gl3.h>
#include <iostream>

namespace Eendgine {

class ShaderProgram {
    public:
        ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
        void use();
        unsigned int getProgramID() { return _programID; };
        void setInt(std::string name, int value) {
            glUniform1i(glGetUniformLocation(_programID, name.c_str()), value);
        }

    private:
        void compileShader(unsigned int id, std::string shaderPath);
        unsigned int _programID;
        unsigned int _vertexShaderID;
        unsigned int _fragmentShaderID;
};
} // namespace Eendgine
