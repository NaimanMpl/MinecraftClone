#include "treebuilder.h"
#include "material.h"

void buildTree(Chunk* chunk, int x, int y, int z) {
    const int TREE_HEIGHT = 5;
    for (int treeY = y; treeY < y + TREE_HEIGHT; treeY++) {
        chunk->addBlock(new Block(Material::OAK_WOOD, x, treeY, z));
    }
}