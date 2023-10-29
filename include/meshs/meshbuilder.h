#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include <vector>
#include "../game_configuration.h"
#include "world/block.h"

namespace BlockModel {

    static const glm::vec3 PZ_POS[] = {
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f)
	};

    static const glm::vec3 NZ_POS[] = {
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f)
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
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
    };

    static const glm::vec3 NX_POS[] = {
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
	};

    static const glm::vec3 PY_POS[] = {
        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, 0.5f)
	};

    static const glm::vec3 NY_POS[] = {
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f)
	};
};

namespace QuadModel {
    static const glm::vec3 PZ_POS[] = {
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f, 0.5f, 0.0f),
        glm::vec3(0.5f, 0.5f, 0.0f),
        glm::vec3(0.5f, 0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f, -0.5f, 0.0f)
    };

    static const glm::vec3 PX_POS[] = {
        glm::vec3(0.0f, -0.5f, 0.5f),
        glm::vec3(0.0f, 0.5f, 0.5f),
        glm::vec3(0.0f, 0.5f, -0.5f),
        glm::vec3(0.0f, 0.5f, -0.5f),
        glm::vec3(0.0f, -0.5f, -0.5f),
        glm::vec3(0.0f, -0.5f, 0.5f)
    };
};

class MeshBuilder {
    private:
        static void addVertex(std::vector<Vertex>& vertices, int x, int y, int z, glm::vec3 position, glm::vec2 textureCoord, glm::vec3 normal, unsigned int voxelID, unsigned int faceID, unsigned int aoID);
        static glm::vec2 calculateTextureCoords(Material material, int k, BlockFace faceID);
        static glm::vec2 calculateCubeTextureCoords(Material material, int k, BlockFace faceID);
        static void calculateAmbientOcclusion(int worldX, int worldY, int worldZ, char plane, int* ao0, int* ao1, int* ao2, int* ao3);
        static bool isEmpty(int worldX, int worldY, int worldZ, char mode = 'C');
        static void addWaterVertex(std::vector<float>& vertices, int x, int y, int z, glm::vec3 position, glm::vec2 textureCoords);
    public:
        static std::vector<Vertex> buildChunkMesh(int chunkX, int chunkY, int chunkZ, int8_t* blocks);
        static std::vector<float> buildWaterMesh(int chunkX, int chunkY, int chunkZ, int8_t* blocks);
        static std::vector<float> buildQuadMesh(int8_t* blocks);
        static std::vector<Vertex> buildHandMesh();
};

#endif