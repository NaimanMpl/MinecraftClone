#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include "shader.h"

class Texture {

    public:
        GLuint ID;
        GLenum type;
        Texture(const char* image, GLenum type, GLenum slot, GLenum format, GLenum pixelType);

        void texUnit(Shader shader, const char* uniform, GLuint unit);
        void bind();
        void unbind();
        void destroy();

};

#endif