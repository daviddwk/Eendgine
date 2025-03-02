#include <fstream>
#include <print>

#include "fatalError.hpp"

#include "shader.hpp"

namespace Eendgine {

ShaderProgram::ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
    : _programID(0), _vertexShaderID(0), _fragmentShaderID(0) {

    _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    compileShader(_vertexShaderID, vertexShaderPath);
    compileShader(_fragmentShaderID, fragmentShaderPath);

    _programID = glCreateProgram();

    glAttachShader(_programID, _vertexShaderID);
    glAttachShader(_programID, _fragmentShaderID);

    glLinkProgram(_programID);

    glDeleteShader(_vertexShaderID);
    glDeleteShader(_fragmentShaderID);
}

void ShaderProgram::compileShader(unsigned int shaderId, std::string shaderPath) {
    std::ifstream shaderFile(shaderPath);
    if (shaderFile.fail()) {
        perror(shaderPath.c_str());
        fatalError(std::format("Unable to open shader file {}\n", shaderPath));
    }

    std::string fileContents = "";
    std::string line;

    while (std::getline(shaderFile, line)) {
        fileContents += line + "\n";
    }

    shaderFile.close();

    const char* contentsPtr = fileContents.c_str();

    glShaderSource(shaderId, 1, &contentsPtr, nullptr);
    glCompileShader(shaderId);

    int isCompiled;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        fatalError(std::format("Unable to compile shader {}: {}\n", shaderPath, infoLog));
        glDeleteShader(shaderId);
    }
}

void ShaderProgram::use() { glUseProgram(_programID); }
} // namespace Eendgine
