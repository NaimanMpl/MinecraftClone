#include "world/generator/default_world_generator.h"
#include "world/generator/noise_generator.h"
#include "world/biome/biome_manager.h"

DefaultWorldGenerator::DefaultWorldGenerator() {
    this->heightMap = new float*[CHUNK_SIZE];
    for (int i = 0; i < CHUNK_SIZE; i++) {
        heightMap[i] = new float[CHUNK_SIZE];
        for (int j = 0; j < CHUNK_SIZE; j++) heightMap[i][j] = 0;
    }
}

float f(float a, float b, float x) {
    return a*x + b;
}

int DefaultWorldGenerator::calculateHeight(int x, int z) const {
    float continentalness = NoiseGenerator::getSimpleNoise(x, z, NoiseGenerator::TERRAIN1_NOISE_SETTINGS);

    int worldHeight;
    if (-1.0f <= continentalness && continentalness <= -0.8f) {
        return f(-550, -420, continentalness);
    } else if (-0.8f < continentalness && continentalness <= -0.5f) {
        return f(0, 20, continentalness);
    } else if (-0.5f < continentalness && continentalness <= -0.4f) {
        return f(400, 200, continentalness);
    } else if (-0.4f < continentalness && continentalness <= -0.1f) {
        return f(0, 60, continentalness);
    } else if (-0.1f < continentalness && continentalness <= 0.3f) {
        return f(50, 85, continentalness);
    } else if (0.3f < continentalness && continentalness <= 0.6f) {
        return f(33 * 1.0f / 3.0f, 90.0f, continentalness);
    } else {
        return f(50, 80, continentalness);
    }



    return worldHeight;
}

void DefaultWorldGenerator::generateTerrain(Chunk* chunk) {
    for (int i = 0; i < CHUNK_SIZE; i++) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            heightMap[i][j] = 0;
        }
    }
    this->chunk = chunk;
    glm::ivec3 chunkWorldVector = glm::ivec3(chunk->getPosition()) * CHUNK_SIZE;
    int chunkX = chunkWorldVector.x;
    int chunkY = chunkWorldVector.y;
    int chunkZ = chunkWorldVector.z;
    for (unsigned int x = 0; x < CHUNK_SIZE; x++) {
        for (unsigned int z = 0; z < CHUNK_SIZE; z++) {
            int worldX = x + chunkX;
            int worldZ = z + chunkZ;
            Biome* biome = BiomeManager::determineBiome(worldX, worldZ);

            NoiseSettings settings;
            settings.octaves = 4;
            settings.amplitude = 0.0f;
            settings.smoothness = 200.0f;
            settings.offset = 0.0f;
            settings.roughness = 0.57f;
            float continentalness = NoiseGenerator::getSimpleNoise(worldX, worldZ, settings);
            continentalness = NoiseGenerator::spline(continentalness);
            int worldHeight = continentalness * (150 - 45) + 45;
            
            for (unsigned int y = 0; y < CHUNK_SIZE; y++) {
                int worldY = y + chunkY;
                Material material = Material::AIR;

                if (worldY < worldHeight) {
                    if (worldY < worldHeight - 6) {
                        material = Material::STONE;
                    } else {
                        material = biome->getUndergroundMaterial();
                    }
                } else if (worldY == worldHeight) {
                    if (worldY >= 24) {
                        material = biome->getTopMaterial();
                        if (x > 1 && x + 5 < CHUNK_SIZE && y + 6 < CHUNK_SIZE && z > 1 && z + 5 < CHUNK_SIZE) {
                            biome->makeTree(chunk, x, y, z);
                        }
                        if (y + 1 < CHUNK_SIZE)
                            biome->makeFlower(chunk, x, y + 1, z);
                    } else {
                        material = biome->getUndergroundMaterial();
                    }
                } else {
                    if (worldY <= 24) {
                        material = Material::WATER;
                    }
                }

                if (material.getName() == "AIR" || material.getName() == "") continue;

                int8_t block = material.getID();
                chunk->addBlock(x, y, z, block);
            }
        }
    }
}

