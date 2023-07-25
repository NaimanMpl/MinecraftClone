#ifndef MATERIAL_ENUM_H
#define MATERIAL_ENUM_H

class Material {
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

        Material();
    private:
        int x, y;
        Material(int x, int y);
};

#endif