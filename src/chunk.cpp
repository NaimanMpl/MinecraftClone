#include "chunk.h"

Chunk::Chunk() {
    std::fill(std::begin(voxels), std::begin(voxels) + GameConfiguration::CHUNK_SIZE, 0.0f);

    for (unsigned int x = 0; x < GameConfiguration::CHUNK_SIZE; x++) {
        for (unsigned int y = 0; y < GameConfiguration::CHUNK_SIZE; y++) {
            for (unsigned int z = 0; z < GameConfiguration::CHUNK_SIZE; z++) {
                voxels[x + GameConfiguration::CHUNK_SIZE * z + GameConfiguration::CHUNK_AREA * y] = 1.0f;
            }
        }
    }
}