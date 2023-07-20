#include "meshs/meshbuilder.h"

std::vector<Vertex> MeshBuilder::buildChunkMesh(float* voxels) {
    uint8_t vertices[GameConfiguration::CHUNK_VOL * 18 * 5];
    int index = 0;

    for (unsigned x = 0; x < GameConfiguration::CHUNK_SIZE; x++) {
        for (unsigned y = 0; y < GameConfiguration::CHUNK_SIZE; y++) {
            for (unsigned z = 0; z < GameConfiguration::CHUNK_SIZE; z++) {
                int voxelID = voxels[x + y * GameConfiguration::CHUNK_SIZE + z * GameConfiguration::CHUNK_SIZE];
                if (!voxelID) continue;
                
            }
        }
    }
    std::vector<Vertex> none;
    return none;
}