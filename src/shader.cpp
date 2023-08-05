#include "shader.h"
#include "utils.h"
#include <vector>

Shader::Shader() {
    
}

Shader::Shader(const char* shaderFilePath, const char* fragmentFilePath) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string shaderSourceCode = Utils::readFile(shaderFilePath);
    std::string fragmentSourceCode = Utils::readFile(fragmentFilePath);

    const char* shaderFormatedCode = shaderSourceCode.c_str();
    const char* fragmentFormatedCode = fragmentSourceCode.c_str();

    glShaderSource(vertexShader, 1, &shaderFormatedCode, NULL);
    glCompileShader(vertexShader);

    handleError(vertexShader);

    glShaderSource(fragmentShader, 1, &fragmentFormatedCode, NULL);
    glCompileShader(fragmentShader);

    handleError(fragmentShader);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    glLinkProgram(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::handleError(GLuint shaderId) {
    GLint isCompiled = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, infoLog.data());

        glDeleteShader(shaderId);

        std::cerr << "Impossible de compiler le shader ! : \n" << infoLog.data();
    }
}

void Shader::enable() {
    glUseProgram(ID);
}

void Shader::destroy() {
    glDeleteProgram(ID);
}

void Shader::setInt(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
