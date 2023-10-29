#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include <map>
#include "world/chunk.h"
#include "shader.h"
#include "camera.h"
#include "world/block.h"
#include "meshs/blockmesh.h"
#include "meshs/chunkmesh.h"
#include "meshs/handmesh.h"
#include "meshs/hotbarmesh.h"
#include "meshs/watermesh.h"
#include "meshs/blockiconmesh.h"
#include "meshs/squaremesh.h"
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
        Texture blockIconAtlas;
        HandMesh handMesh;
        HotbarMesh hotbarMesh;
        BlockIconMesh blockIconMesh;
        SquareMesh cursorMesh;
        SquareMesh blockSelectedMesh;

        Shader cursorShader;
        Shader defaultShader;
        Shader chunkShader;
        Shader handShader;
        Shader hotbarShader;
        Shader waterShader;
        Shader hotbarIconShader;
        Shader doubleQuadShader;
        Renderer();
        void loadTextures();
        void drawHotbarBlocks(int8_t* blocks);
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
        void drawHotbar(Hotbar hotbar);
        BlockMesh& getBlockMesh();
    
};


#endif