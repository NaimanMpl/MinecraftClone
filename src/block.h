#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

const unsigned int BLOCK_FACES_AMOUNT = 6;

#include <glad/glad.h>
#include <string>

class Block {
    public:
        GLuint ID;
        Block(std::string* blockFaces);
        void bind();
        void unbind();
        void destroy();
};

#endif