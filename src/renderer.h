#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include "buffers/EBO.h"
#include "buffers/VAO.h"
#include "block.h"

namespace Vertices {
    extern GLfloat BLOCK_VERTICES[];
    extern GLuint BLOCK_INDICES[];
    extern GLfloat BLOCK_TEXTURE_COORDS[];
}

class Renderer {

    private:
        VBO blockVBO;
        EBO blockEBO;
        VAO blockVAO;
        Shader shader;
        Renderer();

    public:
        static Renderer& getInstance() {
            static Renderer instance;
            return instance;
        }

        Renderer(const Renderer&) = delete;
        void operator=(const Renderer&) = delete;
    
        VBO getBlockVBO();
        EBO getBlockEBO();
        VAO getBlockVAO();
        Shader getShader();
        void draw(Block block);
    
};


#endif