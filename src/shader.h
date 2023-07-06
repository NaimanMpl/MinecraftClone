#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>

class Shader {
    private:
        void handleError(GLuint shaderId);
    public:
        GLuint ID;
        Shader();
        Shader(const char* shaderSourceCode, const char* fragmentSourceCode);
        void enable();
        void destroy();
        void setInt(const std::string& name, int value);
};

#endif