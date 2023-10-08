#include "world/world.h"
#include "randomgenerator.h"
#include <iostream>

World::World() { }

World::World(WorldType worldType) {
    this->worldType = worldType;
    this->terrainGenerator = new DefaultWorldGenerator();
}

WorldType World::getType() {
    return this->worldType;
}

std::unordered_map<ChunkCoordinates, Chunk*, ChunkCoordinatesHash>& World::getChunks() {
    return this->chunks;
}

uint8_t World::getSeed() {
    return RandomGenerator::getInstance().getSeed();
}

bool World::chunkExistsAt(int x, int y, int z) {
    ChunkCoordinates chunkCoords = ChunkCoordinates{x, y, z};
    return chunks.find(chunkCoords) != chunks.end();
}

bool World::chunkMeshExistsAt(int x, int y, int z) {
    ChunkCoordinates chunkCoords = ChunkCoordinates{x, y, z};
    return chunksMeshs.find(chunkCoords) != chunksMeshs.end();
}

Chunk* World::getChunk(int x, int y, int z) {
    ChunkCoordinates chunkCoords = ChunkCoordinates{x, y, z};
    return chunks.find(chunkCoords) == chunks.end() ? nullptr : chunks[chunkCoords];
}

Chunk*World::getChunkAt(unsigned int worldX, unsigned int worldY, unsigned int worldZ) {
    return this->getChunkAt(glm::vec3(worldX, worldY, worldZ));
}

Chunk* World::getChunkAt(glm::vec3 position) {
    int chunkX = position.x / CHUNK_SIZE;
    int chunkY = position.y / CHUNK_SIZE;
    int chunkZ = position.z / CHUNK_SIZE;

    return this->getChunk(chunkX, chunkY, chunkZ);
}

TerrainGenerator* World::getTerrainGenerator() {
    return this->terrainGenerator;
}

Block* World::getBlockAt(unsigned int worldX, unsigned int worldY, unsigned int worldZ) {
    return this->getBlockAt(glm::vec3(worldX, worldY, worldZ));
}

Block* World::getBlockAt(glm::vec3 position) {
    Chunk*chunk = getChunkAt(position);
    if (chunk == nullptr) return nullptr;
    int blockX = (int) position.x % CHUNK_SIZE;
    int blockY = (int) position.y % CHUNK_SIZE;
    int blockZ = (int) position.z % CHUNK_SIZE;

    return chunk->getBlock(blockX, blockY, blockZ);
}

ChunkMesh* World::getChunkMesh(int x, int y, int z) {
    ChunkCoordinates chunkCoords = ChunkCoordinates{x, y, z};
    return chunksMeshs.find(chunkCoords) == chunksMeshs.end() ? nullptr : chunksMeshs[chunkCoords];
}

void World::addChunk(Chunk* chunk) {
    ChunkCoordinates chunkCoords = ChunkCoordinates{chunk->getX(), chunk->getY(), chunk->getZ()};
    chunks[chunkCoords] = chunk;
}

void World::addChunkMesh(ChunkMesh* chunkMesh) {
    Chunk& chunk = chunkMesh->getChunk();
    chunksMeshs[ChunkCoordinates{chunk.getPosition().x, chunk.getPosition().y, chunk.getPosition().z}] = chunkMesh;
}

std::vector<Point>& World::getTrees() {
    return this->trees;
}

void World::addTree(Point tree) {
    trees.push_back(tree);
}