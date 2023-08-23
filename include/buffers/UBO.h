#ifndef UBO_CLASS_H
#define UBO_CLASS_H

#include <glad/glad.h>

class UBO {
    private:
        GLuint ID;
    public:
        UBO();

        void bind();
        void unbind();
        void destroy();

        GLuint getID();
};

#endif