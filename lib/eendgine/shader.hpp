#pragma once
#include <glad/glad.h>
#include <iostream>

namespace Eendgine {
    
    class ShaderProgram {
        public:
            ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
            void use();

            unsigned int programId = 0;
            unsigned int vertexShaderId = 0;
            unsigned int fragmentShaderId = 0;
        private:
            void compileShader(unsigned int id, std::string shaderPath);
    };
}
