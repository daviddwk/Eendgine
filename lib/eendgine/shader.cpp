#include "shader.hpp"
#include <fstream>

namespace Eendgine {

    ShaderProgram::ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath) {
        
        vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        
        compileShader(vertexShaderId, vertexShaderPath);
        compileShader(fragmentShaderId, fragmentShaderPath);

        programId = glCreateProgram();
        
        glAttachShader(programId, vertexShaderId);
        glAttachShader(programId, fragmentShaderId);
        
        glLinkProgram(programId);
        
        
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

    }

    void ShaderProgram::compileShader(unsigned int shaderId, std::string shaderPath) {

		std::ifstream shaderFile(shaderPath);
        if (shaderFile.fail()) {
            perror(shaderPath.c_str());
            std::cout << "Unable to open file!" << std::endl;
        }
        
        std::string fileContents = "";
        std::string line;

        while (std::getline(shaderFile, line)) {
            fileContents += line + "\n";
        }

        shaderFile.close();

        const char *contentsPtr = fileContents.c_str();

        glShaderSource(shaderId, 1, &contentsPtr, nullptr);
        glCompileShader(shaderId);

        int isCompiled;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            char infoLog[512];
            glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
            std::cout << "Unable to compile shader!" << std::endl;
            std::cout << shaderPath << std::endl;
            std::cout << infoLog << std::endl;

            glDeleteShader(shaderId);
        }
    }

    void ShaderProgram::use() {
        glUseProgram(programId);
    }
    
}
