#include "block.h"
#include "shader.h"
#include <stb/stb_image.h>

Block::Block(std::string* blockFaces) {

    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (int i = 0; i < BLOCK_FACES_AMOUNT; i++) {
        int imageWidth, imageHeight, nrChannels;
        unsigned char* data = stbi_load(blockFaces[i].c_str(), &imageWidth, &imageHeight, &nrChannels, 0);
        if (data) {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                imageWidth,
                imageHeight,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
        }

        stbi_image_free(data);
    }
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


void Block::bind() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void Block::unbind() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Block::destroy() {
    glDeleteTextures(1, &ID);
}