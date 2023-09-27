#pragma once

#include <glad/glad.h>
#include <iostream>

namespace Eendgine {
    
    class Shader {
        public:
            Shader();
            ~Shader();
            void init(std::string vertexShaderPath, std::string fragmentShaderPath); 
            void use();
            unsigned int programId;
        private:
            void compileShader(unsigned int id, std::string shaderPath);
    };
}
