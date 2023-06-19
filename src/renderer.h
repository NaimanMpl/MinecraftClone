#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include "block.h"
#include "shader.h"

class Renderer {

    private:
        Shader shader;
        Renderer();

    public:
        static Renderer& getInstance() {
            static Renderer instance;
            return instance;
        }

        Renderer(const Renderer&) = delete;
        void operator=(const Renderer&) = delete;
    
        Shader getShader();
        void draw(Block block);
    
};


#endif