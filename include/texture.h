#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include "shader.h"

const unsigned int BLOCK_FACES_AMOUNT = 6;

class Texture {

    private:
    public:
        GLuint ID;
        const char* image;
        Texture();
        Texture(const char* image);

        void load();
        void bind();
        void unbind();
        void destroy();

};

#endif