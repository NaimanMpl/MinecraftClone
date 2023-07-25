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
    int x = worldX / GameConfiguration::CHUNK_SIZE;
    int y = worldY / GameConfiguration::CHUNK_SIZE;
    int z = worldZ / GameConfiguration::CHUNK_SIZE;

    if (x < 0 || x >= WORLD_WIDTH) return true;
    if (y < 0 || y >= WORLD_HEIGHT) return true;
    if (z < 0 || z >= WORLD_DEPTH) return true;

    Chunk neighboor = Game::getInstance().getWorld().getChunks()[x][y][z];
    for (auto& block : neighboor.getBlocks()) {
        int blockX = block.getX() + neighboor.getPosition().x * GameConfiguration::CHUNK_SIZE;
        int blockY = block.getY() + neighboor.getPosition().y * GameConfiguration::CHUNK_SIZE;
        int blockZ = block.getZ() + neighboor.getPosition().z * GameConfiguration::CHUNK_SIZE;

        if (blockX == worldX && blockY == worldY && worldZ == blockZ) {
            return false;
        }
    }

    return true;

}

void ChunkMesh::checkNeighboorCollision(Block block, int blockIndex, int x, int y, int z, bool* result) {
    if (x <= 0 || x >= WORLD_WIDTH) return;
    if (y <= 0 || y >= WORLD_HEIGHT) return;
    if (z <= 0 || z >= WORLD_DEPTH) return;
    World& world = Game::getInstance().getWorld();
    Chunk neighboor = world.getChunks()[x][y][z];
    for (int i = 0; i < neighboor.getBlocks().size(); i++) {
        Block neighboorBlock = neighboor.getBlocks().at(i);
        if (block.getX() + 1 == neighboorBlock.getX() && block.getY() == neighboorBlock.getY() && block.getZ() == neighboorBlock.getZ()) {
            *result = true;
        }
    }
}

void ChunkMesh::addVertex(Block block, glm::vec3 position, glm::vec2 textureCoord, glm::vec3 normal, unsigned int voxelID, unsigned int faceID) {
    glm::vec3 blockVector(block.getX(), block.getY(), block.getZ());
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
    std::vector<Block>& blocks = chunk.getBlocks();
    Game& game = Game::getInstance();
    for (int i = 0; i < blocks.size(); i++) {
        Block block = blocks.at(i);
        // Those bools represents what cube faces we should draw based on different axes

        // Adding visibile faces to the chunk mesh
        glm::vec3 blockVector(block.getX(), block.getY(), block.getZ());
        Material material = block.getMaterial();
        
        GLuint voxelID;
        voxelID = (GLuint) (block.getX() + block.getY() + block.getZ());

        int chunkX = chunk.getPosition().x;
        int chunkY = chunk.getPosition().y;
        int chunkZ = chunk.getPosition().z;

        int worldX = block.getX() + chunkX * GameConfiguration::CHUNK_SIZE;
        int worldY = block.getY() + chunkY * GameConfiguration::CHUNK_SIZE;
        int worldZ = block.getZ() + chunkZ * GameConfiguration::CHUNK_SIZE;

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