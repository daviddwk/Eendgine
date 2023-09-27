#pragma once

#include <glad/glad.h>
#include <iostream>

namespace Eendgine {
    
    class ShaderProgram {
        public:
            ShaderProgram();
            ~ShaderProgram();
            void init(std::string vertexShaderPath, std::string fragmentShaderPath); 
            unsigned int programId;
        private:
            void compileShader(unsigned int id, std::string shaderPath);
    };
}
