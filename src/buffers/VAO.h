#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {
    public:
        GLuint ID;
        VAO();

        void linkVBO(VBO VBO, GLuint layout);
        void linkAttrib(VBO VBO, GLuint layout, GLuint componentsSize, GLenum type, GLsizeiptr stride, void* offset);
        void bind();
        void unbind();
        void destroy();

};

#endif