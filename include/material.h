#ifndef MATERIAL_ENUM_H
#define MATERIAL_ENUM_H

#include <string>

enum MaterialType {
    DEFAULT_MATERIAL, CUBE
};

class Material {
    protected:
        std::string name;
        MaterialType type;
        Material(std::string name, int x, int y);
    public:
        static const Material DIRT;
        static const Material BRICK;
        static const Material STONE;
        static const Material SAND;
        static const Material WOOD;
        static const Material WOOL;
        static const Material DIAMOND;

        int getX();
        int getY();
        MaterialType getType();

        Material();
        virtual ~Material() {}
        std::string& getName();
        bool operator==(Material const& material) const {
            return name == material.name;
        }
    private:
        int x, y;
};

#endif