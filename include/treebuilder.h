#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

#include "world/block.h"
#include "world/chunk.h"

void buildTree(Chunk* chunk, int x, int z, int trunkHeight, int worldHeight);
void buildCactus(Chunk* chunk, int x, int z, int cactusHeight, int worldHeight);

#endif