#ifndef BIOME_CLASS_H
#define BIOME_CLASS_H

#include <string>

enum BiomeType {
    PLAINS,
    FOREST,
    MOUNTAINS,
    DESERT
};

class Biome {
    private:
        double frequency;
        BiomeType type;
        Biome();
        Biome(BiomeType type, double frequency);
    public:
        static const Biome PLAINS;
        static const Biome FOREST;
        static const Biome MOUNTAINS;
        static const Biome DESERT;
        double getFrenquency();
        BiomeType getType();
};

#endif
