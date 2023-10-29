#include "treebuilder.h"
#include "world/material.h"
#include "game.h"
#include "utils.h"
#include <iostream>

void buildTree(Chunk* chunk, int x, int z, int trunkHeight, int worldHeight) {
    int leaveTop = worldHeight + trunkHeight - 1;
    for (int trunkY = worldHeight; trunkY < worldHeight + trunkHeight; trunkY++) {
        chunk->addBlock(x, trunkY, z, Material::OAK_WOOD.getID());
    }
    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = 1; dy <= 3; dy++) {
            for (int dz = -2; dz <= 2; dz++) {
                if (abs(dx) + abs(dy) + abs(dz) <= 4) {
                    int leaveX = x + dx;
                    int leaveY = leaveTop + dy;
                    int leaveZ = z + dz;
                    chunk->addBlock(leaveX, leaveY, leaveZ, Material::LEAVE.getID());
                }
            }
        }
    }
}

void buildCactus(Chunk* chunk, int x, int z, int cactusHeight, int worldHeight) {
    int leaveTop = worldHeight + cactusHeight - 1;
    for (int trunkY = worldHeight; trunkY < worldHeight + cactusHeight; trunkY++) {
        chunk->addBlock(x, trunkY, z, Material::CACTUS.getID());
    }
}