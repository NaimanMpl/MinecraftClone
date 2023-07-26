#ifndef CHUNKMESH_CLASS_H
#define CHUNKMESH_CLASS_H

#include "mesh.h"
#include "chunk.h"

namespace BlockModel {

    static const glm::vec3 PZ_POS[] = {
        glm::vec3(-0.5f,0.5f,0.5f),
        glm::vec3(-0.5f,-0.5f,0.5f),
        glm::vec3(0.5f,-0.5f,0.5f),
        glm::vec3(0.5f,-0.5f,0.5f),
        glm::vec3(0.5f,0.5f,0.5f),
        glm::vec3(-0.5f,0.5f,0.5f)
	};

    static const glm::vec3 NZ_POS[] = {
        glm::vec3(-0.5f,0.5f,-0.5f),
        glm::vec3(-0.5f,-0.5f,-0.5f),
        glm::vec3(0.5f,-0.5f,-0.5f),
        glm::vec3(0.5f,-0.5f,-0.5f),
        glm::vec3(0.5f,0.5f,-0.5f),
        glm::vec3(-0.5f,0.5f,-0.5f)
    };

    static const glm::vec2 TEXTURE_COORDS[] = {
        glm::vec2(0.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 0.0f)
    };

    static const glm::vec3 NORMALS[] = {
        glm::vec3(1.0f, 0.0f, 0.0f),   // Normale de la face droite (PX)
        glm::vec3(-1.0f, 0.0f, 0.0f),  // Normale de la face gauche (NX)
        glm::vec3(0.0f, 1.0f, 0.0f),   // Normale de la face supérieure (PY)
        glm::vec3(0.0f, -1.0f, 0.0f),  // Normale de la face inférieure (NY)
        glm::vec3(0.0f, 0.0f, 1.0f),   // Normale de la face avant (PZ)
        glm::vec3(0.0f, 0.0f, -1.0f)   // Normale de la face arrière (NZ)
    };

    static const glm::vec3 PX_POS[] = {
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
    };

    static const glm::vec3 NX_POS[] = {
        glm::vec3(-0.5f,0.5f,-0.5f),
        glm::vec3(-0.5f,-0.5f,-0.5f),
        glm::vec3(-0.5f,-0.5f,0.5f),
        glm::vec3(-0.5f,-0.5f,0.5f),
        glm::vec3(-0.5f,0.5f,0.5f),
        glm::vec3(-0.5f,0.5f,-0.5f)
	};

    static const glm::vec3 PY_POS[] = {
        glm::vec3(-0.5f,0.5f,0.5f),
        glm::vec3(-0.5f,0.5f,-0.5f),
        glm::vec3(0.5f,0.5f,-0.5f),
        glm::vec3(0.5f,0.5f,-0.5f),
        glm::vec3(0.5f,0.5f,0.5f),
        glm::vec3(-0.5f,0.5f,0.5f)
	};

    static const glm::vec3 NY_POS[] = {
			glm::vec3(-0.5f,-0.5f,0.5f),
			glm::vec3(-0.5f,-0.5f,-0.5f),
			glm::vec3(0.5f,-0.5f,-0.5f),
			glm::vec3(0.5f,-0.5f,-0.5f),
			glm::vec3(0.5f,-0.5f,0.5f),
			glm::vec3(-0.5f,-0.5f,0.5f)
	};
};

class ChunkMesh: public Mesh {
    private:
        Chunk chunk;
        void initMesh();
        void addVertex(Block* block, glm::vec3 position, glm::vec2 textureCoord, glm::vec3 normal, unsigned int voxelID, unsigned int faceID);
        glm::vec2 calculateTextureCoords(Material material, int k);
        bool isEmpty(int worldX, int worldY, int worldZ);
    public:
        ChunkMesh();
        ChunkMesh(Chunk chunk);

        Chunk& getChunk();

        void update(Chunk chunk);
        void buildMesh();
        void populate();
};

#endif