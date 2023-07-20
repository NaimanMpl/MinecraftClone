#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#include <glad/glad.h>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "buffers/VBO.h"
#include "buffers/EBO.h"
#include "buffers/VAO.h"
#include "material.h"

class Block {
    private:
        double x, y, z;
        Material material;
        void loadTexture();
    public:
        Block();
        Block(Material material, double x, double y, double z);
        
        Material getMaterial();
        double getX();
        double getY();
        double getZ();

        void setX(double x);
        void setY(double y);
        void setZ(double z);

        
};

#endif