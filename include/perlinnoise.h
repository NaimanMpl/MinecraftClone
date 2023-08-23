#ifndef PERLIN_NOISE_CLASS_H
#define PERLIN_NOISE_CLASS_H

class PerlinNoise {
    public:
        static float getNoise(int x, int z, int octaves, float persistance);
};

#endif