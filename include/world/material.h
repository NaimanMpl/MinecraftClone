#ifndef MATERIAL_ENUM_H
#define MATERIAL_ENUM_H

#include <string>
#include <unordered_map>
#include "../buffers/VBO.h"

enum MaterialType {
    DEFAULT_MATERIAL, CUBE
};

struct Point {
    int x;
    int y;
};

class Material {
    private:
        int x, y;
        unsigned int id;
        bool transparent;
        bool solid;
        std::unordered_map<BlockFace, Point> faces;
    protected:
        std::string name;
        MaterialType type;
    public:
        Material(unsigned int id, std::string name, std::unordered_map<BlockFace, Point>& faces);
        Material(unsigned int id, std::string name, int x, int y);
        Material(unsigned int id, std::string name, int x, int y, bool transparent, bool solids);
        static const Material DIRT;
        static const Material BRICK;
        static const Material STONE;
        static const Material SAND;
        static const Material WOOD;
        static const Material WOOL;
        static const Material DIAMOND;
        static const Material GRASS;
        static const Material OAK_WOOD;
        static const Material LEAVE;
        static const Material WATER;
        static const Material SNOW;
        static const Material CACTUS;
        static const Material AIR;

        int getX();
        int getY();
        unsigned int getID();
        MaterialType getType();
        Point getTextureCoord(BlockFace faceID);
        std::string& getName();
        bool isTransparent();
        bool isSolid();

        Material();
        virtual ~Material() {}
        bool operator==(Material const& material) const {
            return name == material.name;
        }
};

#endif