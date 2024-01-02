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
    biomeSettings.amplitude = 1000;
    biomeSettings.smoothness = 2000;
    biomeSettings.offset = 0;
    biomeSettings.roughness = 0.75f;
    return biomeSettings;
}

const NoiseSettings NoiseGenerator::TERRAIN1_NOISE_SETTINGS = getTerrain1Settings();
const NoiseSettings NoiseGenerator::TERRAIN2_NOISE_SETTINGS = getTerrain2Settings();
const NoiseSettings NoiseGenerator::BIOME_NOISE_SETTINGS = getBiomeNoiseSettings();

float lerp(float v0, float v1, float t) {
    return (1 - t) * v0 + t * v1;
}

float NoiseGenerator::spline(float noise) {
    static glm::vec2 points[] = {
        glm::vec2(0.000000f, 0.029412f),
        glm::vec2(0.178104f, 0.078432f),
        glm::vec2(0.214051f, 0.116014f),
        glm::vec2(0.323529f, 0.119281f),
        glm::vec2(0.346405f, 0.192810f),
        glm::vec2(0.464256f, 0.193628f),
        glm::vec2(0.498569f, 0.355800f),
        glm::vec2(0.536815f, 0.378880f),
        glm::vec2(0.657730f, 0.385519f),
        glm::vec2(0.681588f, 0.500766f),
        glm::vec2(0.722438f, 0.511438f),
        glm::vec2(0.737144f, 0.637254f),
        glm::vec2(0.777422f, 0.648692f),
        glm::vec2(0.784135f, 0.737745f),
        glm::vec2(0.807918f, 0.759395f),
        glm::vec2(0.876545f, 0.763684f),
        glm::vec2(0.918665f, 0.964359f),
        glm::vec2(1.000000f, 1.000000f)
    };

    for (int i = 1; i < 18; i++) {
        glm::vec2 p1 = points[i - 1];
        glm::vec2 p2 = points[i];

        if (p1.x <= noise && noise <= p2.x) {
            noise = lerp(p1.y, p2.y, (noise - p1.x) / (p2.x - p1.x));
        }
    }
    return noise;
}

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

float NoiseGenerator::getSimpleNoise(float x, float z, NoiseSettings settings) {
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