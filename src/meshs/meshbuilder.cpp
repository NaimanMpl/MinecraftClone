#include "meshs/meshbuilder.h"
#include "game.h"

void MeshBuilder::calculateAmbientOcclusion(int worldX, int worldY, int worldZ, char plane, int* ao0, int* ao1, int* ao2, int* ao3) {
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

bool MeshBuilder::isEmpty(int worldX, int worldY, int worldZ) {
    int x = worldX / CHUNK_SIZE;
    int y = worldY / CHUNK_SIZE;
    int z = worldZ / CHUNK_SIZE;

    World& world = Game::getInstance().getWorld();

    Chunk* neighboor = world.getChunk(x, y, z);

    if (neighboor == nullptr) {
        neighboor = new Chunk(x, y, z);
        neighboor->load(world.getTerrainGenerator());
        if (!neighboor->isEmpty())
            world.addChunk(neighboor);
    }
 
    int blockNeighboorX = worldX % CHUNK_SIZE; 
    int blockNeighboorY = worldY % CHUNK_SIZE; 
    int blockNeighboorZ = worldZ % CHUNK_SIZE;

    int blockIndex = blockNeighboorX * CHUNK_AREA + blockNeighboorY * CHUNK_SIZE + blockNeighboorZ;
    
    if (blockIndex < CHUNK_VOL && blockNeighboorX >= 0 && blockNeighboorY >= 0 && blockNeighboorZ >= 0) {
        if (neighboor->getBlocks() == nullptr) return true;
        Block* block = neighboor->getBlocks()[blockIndex];
        if (block != nullptr && block->getMaterial().isTransparent()) return true;
        return block == nullptr;
    }

    if (neighboor->getBlocks() == nullptr) {
        delete neighboor;
    } else if (neighboor->isEmpty()) {
        neighboor->unload();
        delete neighboor;
    }

    return true;

}

void MeshBuilder::addVertex(std::vector<Vertex>& vertices, Block* block, glm::vec3 position, glm::vec2 textureCoord, glm::vec3 normal, unsigned int voxelID, unsigned int faceID, unsigned int aoID) {
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

glm::vec2 MeshBuilder::calculateCubeTextureCoords(Material material, int k, BlockFace faceID) {
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

glm::vec2 MeshBuilder::calculateTextureCoords(Block* block, int k, BlockFace faceID) {
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

std::vector<Vertex> MeshBuilder::buildChunkMesh(int chunkX, int chunkY, int chunkZ, Block** blocks) {
    std::vector<Vertex> vertices;
    for (int i = 0; i < CHUNK_VOL; i++) {
        Block* block = blocks[i];

        if (block == nullptr) {
            continue;
        }

        Material material = block->getMaterial();
        
        GLuint voxelID = material.getID();

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
                addVertex(vertices, block, BlockModel::PX_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::RIGHT, ao[k]);
            }
        }

        if (nx) {
            int ao0, ao1, ao2, ao3;
            calculateAmbientOcclusion(worldX - 1, worldY, worldZ, 'X', &ao0, &ao1, &ao2, &ao3);
            int ao[6] = { ao1, ao2, ao3, ao3, ao0, ao1 };
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(block, k, BlockFace::LEFT);
                addVertex(vertices, block, BlockModel::NX_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::LEFT, ao[k]);
            }
        }

        if (py) {
            int ao0, ao1, ao2, ao3;
            calculateAmbientOcclusion(worldX, worldY + 1, worldZ, 'Y', &ao0, &ao1, &ao2, &ao3);
            int ao[6] = { ao0, ao1, ao2, ao2, ao3, ao0 };
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(block, k, BlockFace::TOP);
                addVertex(vertices, block, BlockModel::PY_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::TOP, ao[k]);
            }
        }

        if (ny) {
            int ao0, ao1, ao2, ao3;
            calculateAmbientOcclusion(worldX, worldY - 1, worldZ, 'Y', &ao0, &ao1, &ao2, &ao3);
            int ao[6] = { ao0, ao1, ao2, ao2, ao3, ao0 };
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(block, k, BlockFace::BOTTOM);
                addVertex(vertices, block, BlockModel::NY_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::BOTTOM, ao[k]);
            }
        }

        if (pz) {
            int ao0, ao1, ao2, ao3;
            calculateAmbientOcclusion(worldX, worldY, worldZ + 1, 'Z', &ao0, &ao1, &ao2, &ao3);
            int ao[6] = { ao0, ao3, ao2, ao2, ao1, ao0 };
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(block, k, BlockFace::BACK);
                addVertex(vertices, block, BlockModel::PZ_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::BACK, ao[k]);
            }
        }

        if (nz) {
            int ao0, ao1, ao2, ao3;
            calculateAmbientOcclusion(worldX, worldY, worldZ - 1, 'Z', &ao0, &ao1, &ao2, &ao3);
            int ao[6] = { ao0, ao3, ao2, ao2, ao1, ao0 };
            for (unsigned int k = 0; k < 6; k++) {
                glm::vec2 textureCoord = calculateTextureCoords(block, k, BlockFace::FRONT);
                addVertex(vertices, block, BlockModel::NZ_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::FRONT, ao[k]);
            }
        }
    }
    return vertices;
}

std::vector<Vertex> MeshBuilder::buildHandMesh() {
    std::vector<Vertex> vertices;
    std::vector<Vertex> vertexArray;

    vertexArray.push_back(Vertex{glm::vec3(0.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(10 * 4.0f / 64.0f, 4 * 13.0f / 64.0f)});
    vertexArray.push_back(Vertex{glm::vec3(0.2f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(9 * 4.0f / 64.0f, 4 * 13.0f / 64.0f)});
    vertexArray.push_back(Vertex{glm::vec3(0.2f,  0.0f, -1.0f), glm::vec3(0.0f), glm::vec2(9 * 4.0f / 64.0f, 1.0f)});
    vertexArray.push_back(Vertex{glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f), glm::vec2(10 * 4.0f / 64.0f, 1.0f)});

    vertexArray.push_back(Vertex{glm::vec3(0.2f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(11 * 4.0f / 64.0f, 4 * 13.0f / 64.0f)});
    vertexArray.push_back(Vertex{glm::vec3(0.2f, -1.0f, -1.2f), glm::vec3(0.0f), glm::vec2(10 * 4.0f / 64.0f, 4 * 13.0f / 64.0f)});
    vertexArray.push_back(Vertex{glm::vec3(0.2f,  0.0f, -1.2f), glm::vec3(0.0f), glm::vec2(10 * 4.0f / 64.0f, 1.0f)});
    vertexArray.push_back(Vertex{glm::vec3(0.2f,  0.0f, -1.0f), glm::vec3(0.0f), glm::vec2(11 * 4.0f / 64.0f, 1.0f)});

    for (int i = 0, index = 0; i < 4; i++) {
        vertices.push_back(vertexArray[index++]);
        vertices.push_back(vertexArray[index++]);
        vertices.push_back(vertexArray[index++]);
        vertices.push_back(vertexArray[index++]);
    }

    return vertices;
}