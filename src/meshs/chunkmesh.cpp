#include "meshs/chunkmesh.h"
#include "game.h"
#include "world.h"

ChunkMesh::ChunkMesh() {

}

ChunkMesh::ChunkMesh(Chunk chunk) {
    shader = Shader("../assets/shaders/chunk.vert", "../assets/shaders/chunk.frag");
    this->chunk = chunk;
    buildMesh();
    initMesh();
}

void ChunkMesh::initMesh() {
    VAO.bind();

    VBO VBO(vertices);
    
    VAO.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) 0); // Coords
    VAO.linkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*) (3 * sizeof(float))); // Normals
    VAO.linkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*) (6 * sizeof(float))); // Textures
    VAO.linkAttrib(VBO, 3, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void*) (8 * sizeof(float))); // voxelID
    VAO.linkAttrib(VBO, 4, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void*) (9 * sizeof(float))); // faceID

    VAO.unbind();
    VBO.unbind();
}

Chunk& ChunkMesh::getChunk() {
    return chunk;
}

void ChunkMesh::update(Chunk chunk) {
    this->chunk = chunk;
    buildMesh();
}

glm::vec2 ChunkMesh::calculateTextureCoords(Material material, int k) {
    glm::vec2 textureCoord;
    if (BlockModel::TEXTURE_COORDS[k].x == 0.0f) {
        textureCoord.x = material.getX() * (1.0f / 16.0f);
    } else {
        textureCoord.x = material.getX() * (1.0f / 16.0f) + (1.0f / 16.0f);
    }
    if (BlockModel::TEXTURE_COORDS[k].y == 0.0f) {
        textureCoord.y = material.getY() / 16.0f;
    } else {
        textureCoord.y = material.getY() / 16.0f + (1.0f / 16.0f);
    }
    return BlockModel::TEXTURE_COORDS[k];
}

bool ChunkMesh::isEmpty(int worldX, int worldY, int worldZ) {
    int x = worldX / CHUNK_SIZE;
    int y = worldY / CHUNK_SIZE;
    int z = worldZ / CHUNK_SIZE;

    bool boundedX = 0 <= x && x < WORLD_WIDTH;
    bool boundedY = 0 <= y && y < WORLD_HEIGHT;
    bool boundedZ = 0 <= z && z < WORLD_DEPTH;

    if (!(boundedX && boundedY && boundedZ) || worldX < 0 || worldY < 0 || worldZ < 0) return true;

    Chunk* neighboor = Game::getInstance().getWorld().getChunk(x, y, z);

    if (neighboor == nullptr) return true;

    int blockNeighboorX = worldX % CHUNK_SIZE; 
    int blockNeighboorY = worldY % CHUNK_SIZE; 
    int blockNeighboorZ = worldZ % CHUNK_SIZE;

    int blockIndex = blockNeighboorX * CHUNK_AREA + blockNeighboorY * CHUNK_SIZE + blockNeighboorZ;
    
    if (blockIndex < CHUNK_VOL) {
        Block* block = neighboor->getBlocks()[blockIndex];
        return block == nullptr;
    }

    return true;

}

void ChunkMesh::addVertex(Block* block, glm::vec3 position, glm::vec2 textureCoord, glm::vec3 normal, unsigned int voxelID, unsigned int faceID) {
    glm::vec3 blockVector(block->getX(), block->getY(), block->getZ());
    vertices.push_back(
        Vertex{
            glm::vec3(position + blockVector),
            normal,
            textureCoord,
            voxelID,
            faceID
        }
    );
}



void ChunkMesh::buildMesh() {
    Block** blocks = chunk.getBlocks();
    Game& game = Game::getInstance();
    for (int i = 0; i < CHUNK_VOL; i++) {
        Block* block = blocks[i];

        if (block == nullptr) {
            continue;
        }

        Material material = block->getMaterial();
        
        GLuint voxelID;
        voxelID = (GLuint) (block->getX() + block->getY() + block->getZ());

        int chunkX = chunk.getPosition().x;
        int chunkY = chunk.getPosition().y;
        int chunkZ = chunk.getPosition().z;

        int worldX = block->getX() + chunkX * CHUNK_SIZE;
        int worldY = block->getY() + chunkY * CHUNK_SIZE;
        int worldZ = block->getZ() + chunkZ * CHUNK_SIZE;

        bool px = isEmpty(worldX + 1, worldY, worldZ);
        bool nx = isEmpty(worldX - 1, worldY, worldZ);
        bool py = isEmpty(worldX, worldY + 1, worldZ);
        bool ny = isEmpty(worldX, worldY - 1, worldZ);
        bool pz = isEmpty(worldX, worldY, worldZ + 1);
        bool nz = isEmpty(worldX, worldY, worldZ - 1);

        if (px) {
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(material, k);
                addVertex(block, BlockModel::PX_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::RIGHT);
            }
        }

        if (nx) {
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(material, k);
                addVertex(block, BlockModel::NX_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::LEFT);
            }
        }

        if (py) {
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(material, k);
                addVertex(block, BlockModel::PY_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::TOP);
            }
        }

        if (ny) {
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(material, k);
                addVertex(block, BlockModel::NY_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::BOTTOM);
            }
        }

        if (pz) {
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(material, k);
                addVertex(block, BlockModel::PZ_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::FRONT);
            }
        }

        if (nz) {
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(material, k);
                addVertex(block, BlockModel::NZ_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::BACK);
            }
        }
    }
}

void ChunkMesh::populate() {

}