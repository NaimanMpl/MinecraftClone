#include "perlinnoise.h"
#include "world/chunk.h"
#include "world/world.h"
#include <glm/gtc/noise.hpp>
#include <cstdlib>

float PerlinNoise::getNoise(int x, int z, int octaves, float persistance) {
    float frequency = 1 / 64.0f;
    float amplitude = 1.0f;
    float noise = 0.0f;
    for (int i = 0; i < octaves; i++) {
        noise += glm::perlin(glm::vec2(x, z) * frequency) * amplitude;
        amplitude *= persistance;
        frequency *= 2;
    }
    return noise * (1 - persistance) / (1 - amplitude);
}