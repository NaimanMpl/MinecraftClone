#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include <map>
#include "world/chunk.h"
#include "shader.h"
#include "camera.h"
#include "world/block.h"
#include "meshs/blockmesh.h"
#include "meshs/chunkmesh.h"
#include "meshs/imagemesh.h"
#include "meshs/handmesh.h"
#include "meshs/hotbarmesh.h"
#include "meshs/watermesh.h"
#include "buffers/UBO.h"
#include "texture.h"

class Renderer {

    private:
        BlockMesh blockMesh;
        std::map<Material, GLuint> textures;
        Texture blockAtlas;
        Texture frameTexture;
        Texture iconsTexture;
        Texture skinTexture;
        Texture crosshairTexture;
        Texture hotbarTexture;
        ImageMesh cursorMesh;
        HandMesh handMesh;
        HotbarMesh hotbarMesh;

        Shader defaultShader;
        Shader chunkShader;
        Shader handShader;
        Shader hotbarShader;
        Shader waterShader;
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
        void drawHand();
        void drawHotbar();
        BlockMesh& getBlockMesh();
    
};


#endif