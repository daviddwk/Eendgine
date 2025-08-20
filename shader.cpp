#include <fstream>
#include <print>

#include "fatalError.hpp"

#include "shader.hpp"

namespace Eendgine {

ShaderProgram::ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
    : m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0) {

    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    compileShader(m_vertexShaderID, vertexShaderPath);
    compileShader(m_fragmentShaderID, fragmentShaderPath);

    m_programID = glCreateProgram();

    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);

    glLinkProgram(m_programID);

    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
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

void ShaderProgram::use() { glUseProgram(m_programID); }
} // namespace Eendgine
