#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include "block.h"
#include "shader.h"
#include "camera.h"
#include "meshs/blockmesh.h"

class Renderer {

    private:
        VBO blockVBO;
        EBO blockEBO;
        BlockMesh blockMesh;
        Renderer();

    public:
        static Renderer& getInstance() {
            static Renderer instance;
            return instance;
        }

        Renderer(const Renderer&) = delete;
        void operator=(const Renderer&) = delete;
    
        void draw(Camera camera, Block block);
        BlockMesh& getBlockMesh();
    
};


#endif