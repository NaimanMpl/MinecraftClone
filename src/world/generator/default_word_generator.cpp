#include "world/generator/default_world_generator.h"
#include "world/generator/noise_generator.h"
#include "world/biome/biome_manager.h"

DefaultWorldGenerator::DefaultWorldGenerator() {
    fillHeightMap();
}

void DefaultWorldGenerator::fillHeightMap() {
    for (int worldX = 0; worldX < WORLD_WIDTH * CHUNK_SIZE; worldX++) {
        for (int worldZ = 0; worldZ < WORLD_DEPTH * CHUNK_SIZE; worldZ++) {       
            heightMap[worldX * WORLD_WIDTH * CHUNK_SIZE + worldZ] = calculateHeight(worldX, worldZ);
        }
    }
}

float rounded(const glm::vec2& coord) {
    auto bump = [](float t) { return glm::max(0.0f, 1.0f - std::pow(t, 6.0f)); };
    float b = bump(coord.x) * bump(coord.y);
    return b * 0.9f;
}

int DefaultWorldGenerator::calculateHeight(int x, int z) const {
    float firstNoise = NoiseGenerator::getNoise(x, z, NoiseGenerator::TERRAIN1_NOISE_SETTINGS);
    float secondNoise = NoiseGenerator::getNoise(x, z, NoiseGenerator::TERRAIN2_NOISE_SETTINGS);
    float continentalness = firstNoise * secondNoise;
    glm::vec2 coord = (glm::vec2(x, z) - WORLD_WIDTH * CHUNK_SIZE / 2.0f) / static_cast<float>(WORLD_DEPTH * CHUNK_SIZE) * 2.0f;
    float island = rounded(coord) * 1.25;
    int worldHeight = static_cast<int>((continentalness * NoiseGenerator::TERRAIN1_NOISE_SETTINGS.amplitude + NoiseGenerator::TERRAIN1_NOISE_SETTINGS.offset) * island - 5);
    return worldHeight;
}

void DefaultWorldGenerator::generateTerrain(Chunk* chunk) {
    glm::ivec3 chunkWorldVector = glm::ivec3(chunk->getPosition()) * CHUNK_SIZE;
    int chunkX = chunkWorldVector.x;
    int chunkY = chunkWorldVector.y;
    int chunkZ = chunkWorldVector.z;
    BiomeManager biomeManager;
    for (unsigned int x = 0; x < CHUNK_SIZE; x++) {
        for (unsigned int z = 0; z < CHUNK_SIZE; z++) {
            int worldX = x + chunkX;
            int worldZ = z + chunkZ;
            int worldHeight = heightMap[worldX * WORLD_WIDTH * CHUNK_SIZE + worldZ];
            Biome* biome = biomeManager.determineBiome(worldX, worldZ);

            for (unsigned int y = 0; y < CHUNK_SIZE; y++) {
                int worldY = y + chunkY;
                Material material = Material::AIR;

                if (worldY < worldHeight) {
                    if (worldY < worldHeight - 6) {
                        material = Material::STONE;
                    } else if (worldHeight - 6 <= worldY && worldY < worldHeight - 3) {
                        material = biome->getUndergroundMaterial();
                    } else {
                        material = biome->getUndergroundMaterial();
                    }
                } else if (worldY == worldHeight) {
                    material = biome->getTopMaterial();
                    if (x > 1 && x + 5 < CHUNK_SIZE && y + 6 < CHUNK_SIZE && z > 1 && z + 5 < CHUNK_SIZE) {
                        biome->makeTree(chunk, x, y, z);
                    }
                } else if (worldY > worldHeight) {
                    if (worldY <= 16) {
                        material = Material::WATER;
                    }
                }

                if (material.getName() == "AIR" || material.getName() == "") continue;

                Block* block = new Block(material, x, y, z);
                chunk->addBlock(block);
            }
        }
    }
}

