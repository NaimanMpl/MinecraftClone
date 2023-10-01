#include "world/generator/noise_generator.h"
#include "FastNoise.h"
#include "game.h"

NoiseSettings getTerrain1Settings() {
    NoiseSettings settings;
    settings.octaves = 6;
    settings.amplitude = 105.0f;
    settings.smoothness = 205.0f;
    settings.roughness = 0.58f;
    settings.offset = 18;
    return settings;
}

NoiseSettings getTerrain2Settings() {
    NoiseSettings settings;
    settings.octaves = 4;
    settings.amplitude = 20.0f;
    settings.smoothness = 200.0f;
    settings.roughness = 0.45f;
    settings.offset = 0;
    return settings;
}

NoiseSettings getBiomeNoiseSettings() {
    NoiseSettings biomeSettings;
    biomeSettings.octaves = 5;
    biomeSettings.amplitude = 800;
    biomeSettings.smoothness = 2000;
    biomeSettings.offset = 0;
    biomeSettings.roughness = 0.75f;
    return biomeSettings;
}

const NoiseSettings NoiseGenerator::TERRAIN1_NOISE_SETTINGS = getTerrain1Settings();
const NoiseSettings NoiseGenerator::TERRAIN2_NOISE_SETTINGS = getTerrain2Settings();
const NoiseSettings NoiseGenerator::BIOME_NOISE_SETTINGS = getBiomeNoiseSettings();

float NoiseGenerator::getNoise(float x, float z, NoiseSettings settings) {

    FastNoiseLite noiseGenerator;
    World& world = Game::getInstance().getWorld();
    noiseGenerator.SetSeed(world.getSeed());
    noiseGenerator.SetFrequency(0.8);
    noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);
    float value = 0.0f;
    float amplitudeSum = 0.0f;
    for (unsigned int i = 0; i < settings.octaves; i++) {
        float frequency = glm::pow(2.0, i);
        float amplitude = glm::pow(settings.roughness, i);
        float noiseX = x * frequency / settings.smoothness;
        float noiseZ = z * frequency / settings.smoothness;

        float noise = noiseGenerator.GetNoise(noiseX, noiseZ);
        noise = (noise + 1.0f) / 2.0f;
        value += noise * amplitude;
        amplitudeSum += amplitude;
    }
    return value / amplitudeSum;
}

float NoiseGenerator::getHeight(float x, float z, NoiseSettings settings) {

    FastNoiseLite noiseGenerator;
    World& world = Game::getInstance().getWorld();
    noiseGenerator.SetSeed(world.getSeed());
    noiseGenerator.SetFrequency(0.8);
    noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Perlin);
    float value = 0.0f;
    float amplitudeSum = 0.0f;
    for (unsigned int i = 0; i < settings.octaves; i++) {
        float frequency = glm::pow(2.0, i);
        float amplitude = glm::pow(settings.roughness, i);
        float noiseX = x * frequency / settings.smoothness;
        float noiseZ = z * frequency / settings.smoothness;

        float noise = noiseGenerator.GetNoise(noiseX, noiseZ);
        value += noise * amplitude;
    }
    float height = (((value / 2.1) + 1.2) * settings.amplitude) + settings.offset;
    return height > 0 ? height : 1;
}