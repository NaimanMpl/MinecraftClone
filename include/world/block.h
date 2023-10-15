#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#include <glad/glad.h>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "../buffers/VBO.h"
#include "../buffers/EBO.h"
#include "../buffers/VAO.h"
#include "world/material.h"

class Block {
    private:
        int x, y, z;
        Material material;
    public:
        Block();
        Block(Material material, int x, int y, int z);
        
        Material getMaterial();
        int getX();
        int getY();
        int getZ();

        void setX(int x);
        void setY(int y);
        void setZ(int z);

        void toString();

        
};

#endif