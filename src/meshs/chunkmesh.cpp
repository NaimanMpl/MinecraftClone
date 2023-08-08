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
    VAO.linkAttrib(VBO, 5, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void*) (10 * sizeof(float))); // aoID

    VAO.unbind();
    VBO.unbind();
}

Chunk& ChunkMesh::getChunk() {
    return chunk;
}

void ChunkMesh::update(Chunk chunk) {
    this->chunk = chunk;
    vertices.clear();
    buildMesh();
    initMesh();
}

void ChunkMesh::calculateAmbientOcclusion(int worldX, int worldY, int worldZ, char plane, int* ao0, int* ao1, int* ao2, int* ao3) {
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
    switch (plane) {
        case 'Y':
            a = isEmpty(worldX - 1, worldY, worldZ);
            b = isEmpty(worldX - 1, worldY, worldZ + 1);
            c = isEmpty(worldX    , worldY, worldZ + 1);
            d = isEmpty(worldX + 1, worldY, worldZ + 1);
            e = isEmpty(worldX + 1, worldY, worldZ    );
            f = isEmpty(worldX + 1, worldY, worldZ - 1);
            g = isEmpty(worldX    , worldY, worldZ - 1);
            h = isEmpty(worldX - 1, worldY, worldZ - 1);
            break;
        case 'X':
            a = isEmpty(worldX, worldY + 1, worldZ    );
            b = isEmpty(worldX, worldY + 1, worldZ + 1);
            c = isEmpty(worldX, worldY    , worldZ + 1);
            d = isEmpty(worldX, worldY - 1, worldZ + 1);
            e = isEmpty(worldX, worldY - 1, worldZ    );
            f = isEmpty(worldX, worldY - 1, worldZ - 1);
            g = isEmpty(worldX, worldY    , worldZ - 1);
            h = isEmpty(worldX, worldY + 1, worldZ - 1);
            break;
        case 'Z':
            a = isEmpty(worldX    , worldY + 1, worldZ);
            b = isEmpty(worldX - 1, worldY + 1, worldZ);
            c = isEmpty(worldX - 1, worldY    , worldZ);
            d = isEmpty(worldX - 1, worldY - 1, worldZ);
            e = isEmpty(worldX    , worldY - 1, worldZ);
            f = isEmpty(worldX + 1, worldY - 1, worldZ);
            g = isEmpty(worldX + 1, worldY    , worldZ);
            h = isEmpty(worldX + 1, worldY + 1, worldZ);
            break;
    }
    *ao0 = a + b + c;
    *ao1 = g + h + a;
    *ao2 = e + f + g;
    *ao3 = c + d + e;
}

glm::vec2 ChunkMesh::calculateCubeTextureCoords(Material material, int k, BlockFace faceID) {
    Point point = material.getTextureCoord(faceID);
    glm::vec2 textureCoord;
    if (BlockModel::TEXTURE_COORDS[k].x == 0.0f) {
        textureCoord.x = point.x * (1.0f / 16.0f);
    } else {
        textureCoord.x = point.x * (1.0f / 16.0f) + (1.0f / 16.0f);
    }
    if (BlockModel::TEXTURE_COORDS[k].y == 0.0f) {
        textureCoord.y = point.y / 16.0f;
    } else {
        textureCoord.y = point.y / 16.0f + (1.0f / 16.0f);
    }
    return textureCoord;
}

glm::vec2 ChunkMesh::calculateTextureCoords(Block* block, int k, BlockFace faceID) {
    Material material = block->getMaterial();
    if (material.getType() == MaterialType::CUBE) {
        return calculateCubeTextureCoords(material, k, faceID);
    }
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
    return textureCoord;
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

void ChunkMesh::addVertex(Block* block, glm::vec3 position, glm::vec2 textureCoord, glm::vec3 normal, unsigned int voxelID, unsigned int faceID, unsigned int aoID) {
    glm::vec3 blockVector(block->getX(), block->getY(), block->getZ());
    vertices.push_back(
        Vertex{
            glm::vec3(position + blockVector),
            normal,
            textureCoord,
            voxelID,
            faceID,
            aoID
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
        
        GLuint voxelID = material.getID();

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
            int ao0, ao1, ao2, ao3;
            calculateAmbientOcclusion(worldX + 1, worldY, worldZ, 'X', &ao0, &ao1, &ao2, &ao3);
            int ao[6] = { ao1, ao2, ao3, ao3, ao0, ao1 };
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(block, k, BlockFace::RIGHT);
                addVertex(block, BlockModel::PX_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::RIGHT, ao[k]);
            }
        }

        if (nx) {
            int ao0, ao1, ao2, ao3;
            calculateAmbientOcclusion(worldX - 1, worldY, worldZ, 'X', &ao0, &ao1, &ao2, &ao3);
            int ao[6] = { ao1, ao2, ao3, ao3, ao0, ao1 };
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(block, k, BlockFace::LEFT);
                addVertex(block, BlockModel::NX_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::LEFT, ao[k]);
            }
        }

        if (py) {
            int ao0, ao1, ao2, ao3;
            calculateAmbientOcclusion(worldX, worldY + 1, worldZ, 'Y', &ao0, &ao1, &ao2, &ao3);
            int ao[6] = { ao0, ao1, ao2, ao2, ao3, ao0 };
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(block, k, BlockFace::TOP);
                addVertex(block, BlockModel::PY_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::TOP, ao[k]);
            }
        }

        if (ny) {
            int ao0, ao1, ao2, ao3;
            calculateAmbientOcclusion(worldX, worldY - 1, worldZ, 'Y', &ao0, &ao1, &ao2, &ao3);
            int ao[6] = { ao0, ao1, ao2, ao2, ao3, ao0 };
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(block, k, BlockFace::BOTTOM);
                addVertex(block, BlockModel::NY_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::BOTTOM, ao[k]);
            }
        }

        if (pz) {
            int ao0, ao1, ao2, ao3;
            calculateAmbientOcclusion(worldX, worldY, worldZ + 1, 'Z', &ao0, &ao1, &ao2, &ao3);
            int ao[6] = { ao0, ao3, ao2, ao2, ao1, ao0 };
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(block, k, BlockFace::BACK);
                addVertex(block, BlockModel::PZ_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::BACK, ao[k]);
            }
        }

        if (nz) {
            int ao0, ao1, ao2, ao3;
            calculateAmbientOcclusion(worldX, worldY, worldZ - 1, 'Z', &ao0, &ao1, &ao2, &ao3);
            int ao[6] = { ao0, ao3, ao2, ao2, ao1, ao0 };
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(block, k, BlockFace::FRONT);
                addVertex(block, BlockModel::NZ_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::FRONT, ao[k]);
            }
        }
    }
}

void ChunkMesh::populate() {

}