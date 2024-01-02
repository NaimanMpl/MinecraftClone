#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

#include <cstdint>

struct NoiseSettings {
    unsigned int octaves;
    float amplitude;
    float roughness;
    float smoothness;
    float offset;
};

class NoiseGenerator {
    public:
        static const NoiseSettings TERRAIN1_NOISE_SETTINGS;
        static const NoiseSettings TERRAIN2_NOISE_SETTINGS;
        static const NoiseSettings BIOME_NOISE_SETTINGS;
        
        static float getNoise(float x, float z, NoiseSettings settings);
        static float getHeight(float x, float z, NoiseSettings settings);
        static float getSimpleNoise(float x, float z, NoiseSettings settings);
        static float spline(float noise);
};

#endif