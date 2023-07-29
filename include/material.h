#ifndef MATERIAL_ENUM_H
#define MATERIAL_ENUM_H

#include <string>
#include <unordered_map>
#include "buffers/VBO.h"

enum MaterialType {
    DEFAULT_MATERIAL, CUBE
};

struct Point {
    unsigned int x;
    unsigned int y;
};

class Material {
    private:
        int x, y;
        unsigned int id;
        std::unordered_map<BlockFace, Point> faces;
    protected:
        std::string name;
        MaterialType type;
    public:
        Material(unsigned int id, std::string name, std::unordered_map<BlockFace, Point>& faces);
        Material(unsigned int id, std::string name, int x, int y);
        static const Material DIRT;
        static const Material BRICK;
        static const Material STONE;
        static const Material SAND;
        static const Material WOOD;
        static const Material WOOL;
        static const Material DIAMOND;
        static const Material GRASS;
        static const Material OAK_WOOD;
        static const Material WATER;

        int getX();
        int getY();
        unsigned int getID();
        MaterialType getType();
        Point getTextureCoord(BlockFace faceID);
        std::string& getName();

        Material();
        virtual ~Material() {}
        bool operator==(Material const& material) const {
            return name == material.name;
        }
};

#endif