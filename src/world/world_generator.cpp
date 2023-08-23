#include "world/world_generator.h"
#include "FastNoise.h"
#include "game.h"

Biome WorldGenerator::determineBiome(float biomeNoiseValue) {
    if (biomeNoiseValue < 0.2) {
        return Biome::PLAINS;
    } else if (biomeNoiseValue < 0.4) {
        return Biome::FOREST;
    } else if (biomeNoiseValue < 0.6) {
        return Biome::MOUNTAINS;
    } else {
        return Biome::DESERT;
    }
}

float WorldGenerator::getBiomeNoise(float x, float z) {
    FastNoiseLite noiseGenerator;
    World& world = Game::getInstance().getWorld();
    noiseGenerator.SetSeed(world.getSeed());
    noiseGenerator.SetFractalOctaves(4);
    noiseGenerator.SetFrequency(0.01);
    return noiseGenerator.GetNoise(x, z);
}

float WorldGenerator::getTerrainNoise(float x, float z) {
    FastNoiseLite noiseGenerator;
    World& world = Game::getInstance().getWorld();
    noiseGenerator.SetSeed(world.getSeed());
    noiseGenerator.SetFractalOctaves(4);
    return noiseGenerator.GetNoise(x, z);
}