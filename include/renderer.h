#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include <map>
#include "chunk.h"
#include "shader.h"
#include "camera.h"
#include "block.h"
#include "meshs/blockmesh.h"
#include "meshs/chunkmesh.h"
#include "meshs/imagemesh.h"
#include "texture.h"

class Renderer {

    private:
        VBO blockVBO;
        EBO blockEBO;
        BlockMesh blockMesh;
        std::map<Material, GLuint> textures;
        Texture blockAtlas;
        Texture frameTexture;
        Texture iconsTexture;
        Shader defaultShader;
        ImageMesh cursorMesh;
        Renderer();
        void loadTextures();

    public:
        static Renderer& getInstance() {
            static Renderer instance;
            return instance;
        }

        Renderer(const Renderer&) = delete;
        void operator=(const Renderer&) = delete;
    
        void draw(Camera& camera, Chunk chunk, ChunkMesh chunkMesh);
        void drawCursor(Camera& camera);
        void drawVoxel(Camera& camera);
        BlockMesh& getBlockMesh();
    
};


#endif