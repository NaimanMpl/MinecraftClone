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
        int id;
        bool transparent;
        bool solid;
        std::unordered_map<BlockFace, Point> faces;
    protected:
        std::string name;
        MaterialType type;
    public:
        Material(int id, std::string name, std::unordered_map<BlockFace, Point>& faces);
        Material(int id, std::string name, int x, int y);
        Material(int id, std::string name, int x, int y, bool transparent, bool solids);
        static Material DIRT;
        static Material BRICK;
        static Material STONE;
        static Material SAND;
        static Material WOOD;
        static Material WOOL;
        static Material DIAMOND;
        static Material GRASS;
        static Material OAK_WOOD;
        static Material LEAVE;
        static Material WATER;
        static Material SNOW;
        static Material CACTUS;
        static Material AIR;

        int getX();
        int getY();
        int getID();
        MaterialType getType();
        Point getTextureCoord(BlockFace faceID);
        std::string& getName();
        bool isTransparent();
        bool isSolid();

        Material();
        bool operator==(Material const& material) const {
            return name == material.name;
        }
};

#endif