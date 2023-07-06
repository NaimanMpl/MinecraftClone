#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include <vector>
#include "vertex.h"

class VBO {
    public:
        GLuint ID;
        VBO();
        VBO(std::vector<Vertex>& vertices);

        void bind();
        void unbind();
        void destroy();
};

#endif