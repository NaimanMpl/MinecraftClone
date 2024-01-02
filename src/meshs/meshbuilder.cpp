#include "meshs/meshbuilder.h"
#include "game.h"
#include "utils.h"

void MeshBuilder::calculateAmbientOcclusion(int worldX, int worldY, int worldZ, char plane, int* ao0, int* ao1, int* ao2, int* ao3) {
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
    switch (plane) {
        case 'Y':
            a = isEmpty(worldX    , worldY, worldZ - 1);
            b = isEmpty(worldX - 1, worldY, worldZ - 1);
            c = isEmpty(worldX - 1, worldY, worldZ    );
            d = isEmpty(worldX - 1, worldY, worldZ + 1);
            e = isEmpty(worldX    , worldY, worldZ + 1);
            f = isEmpty(worldX + 1, worldY, worldZ + 1);
            g = isEmpty(worldX + 1, worldY, worldZ    );
            h = isEmpty(worldX + 1, worldY, worldZ - 1);
            break;
        case 'X':
            a = isEmpty(worldX, worldY    , worldZ - 1);
            b = isEmpty(worldX, worldY - 1, worldZ - 1);
            c = isEmpty(worldX, worldY - 1, worldZ    );
            d = isEmpty(worldX, worldY - 1, worldZ + 1);
            e = isEmpty(worldX, worldY    , worldZ + 1);
            f = isEmpty(worldX, worldY + 1, worldZ + 1);
            g = isEmpty(worldX, worldY + 1, worldZ    );
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
    *ao0 = c + d + e;
    *ao1 = a + b + c;
    *ao2 = a + h + g;
    *ao3 = g + e + f;
}

bool MeshBuilder::isEmpty(int worldX, int worldY, int worldZ, char mode) {
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
        int8_t block = neighboor->getBlocks()[blockIndex];
        if (mode == 'W') {
            if (block == Material::WATER.getID()) return false;
        } else if (mode == 'C') {
            if (block == Material::WATER.getID()) return true;
        }
        Material material = Utils::getMaterialFromBlock(block);
        if (material.getType() == MaterialType::QUAD) return true;
        if (block != -1 && material.isTransparent()) return true;
        return block == -1;
    }

    if (neighboor->getBlocks() == nullptr) {
        delete neighboor;
    } else if (neighboor->isEmpty()) {
        neighboor->unload();
        delete neighboor;
    }

    return true;

}

void MeshBuilder::addVertex(std::vector<Vertex>& vertices, int x, int y, int z, glm::vec3 position, glm::vec2 textureCoord, glm::vec3 normal, unsigned int voxelID, unsigned int faceID, unsigned int aoID) {
    glm::vec3 blockVector(x, y, z);
    vertices.push_back(
        Vertex{
            glm::vec3(position + blockVector),
            normal,
            textureCoord,
            static_cast<float>(voxelID),
            static_cast<float>(faceID),
            static_cast<float>(aoID)
        }
    );
}

void MeshBuilder::addWaterVertex(std::vector<float>& vertices, int x, int y, int z, glm::vec3 position, glm::vec2 textureCoord) {
    vertices.push_back(position.x + x);
    vertices.push_back(position.y + y);
    vertices.push_back(position.z + z);
    vertices.push_back(textureCoord.x);
    vertices.push_back(textureCoord.y);
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
        textureCoord.y = (15.0f - point.y) / 16.0f;
    } else {
        textureCoord.y = (15.0f - point.y) / 16.0f + (1.0f / 16.0f);
    }
    return textureCoord;
}

glm::vec2 MeshBuilder::calculateTextureCoords(Material material, int k, BlockFace faceID) {
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
        textureCoord.y = (15.0f - material.getY()) / 16.0f;
    } else {
        textureCoord.y = (15.0f - material.getY()) / 16.0f + (1.0f / 16.0f);
    }
    return textureCoord;
}

std::vector<Vertex> MeshBuilder::buildChunkMesh(int chunkX, int chunkY, int chunkZ, int8_t* blocks) {
    std::vector<Vertex> vertices;
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                int8_t block = blocks[x * CHUNK_AREA + y * CHUNK_SIZE + z];
                Material material = Utils::getMaterialFromBlock(block);

                if (block == -1 || block == Material::WATER.getID() || material.getType() == MaterialType::QUAD) {
                    continue;
                }

                GLuint voxelID = material.getID();

                int worldX = x + chunkX * CHUNK_SIZE;
                int worldY = y + chunkY * CHUNK_SIZE;
                int worldZ = z + chunkZ * CHUNK_SIZE;

                bool px = isEmpty(worldX + 1, worldY, worldZ);
                bool nx = isEmpty(worldX - 1, worldY, worldZ);
                bool py = isEmpty(worldX, worldY + 1, worldZ);
                bool ny = isEmpty(worldX, worldY - 1, worldZ);
                bool pz = isEmpty(worldX, worldY, worldZ + 1);
                bool nz = isEmpty(worldX, worldY, worldZ - 1);

                if (px) {
                    int ao0, ao1, ao2, ao3;
                    calculateAmbientOcclusion(worldX + 1, worldY, worldZ, 'X', &ao3, &ao0, &ao1, &ao2);
                    int ao[6] = { ao0, ao1, ao2, ao2, ao3, ao0 };
                    for (unsigned int k = 0; k < 6; k++) {
                        glm::vec2 textureCoord = calculateTextureCoords(material, k, BlockFace::RIGHT);
                        addVertex(vertices, x, y, z, BlockModel::PX_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::RIGHT, ao[k]);
                    }
                }

                if (nx) {
                    int ao0, ao1, ao2, ao3;
                    calculateAmbientOcclusion(worldX - 1, worldY, worldZ, 'X', &ao3, &ao0, &ao1, &ao2);
                    int ao[6] = { ao0, ao1, ao2, ao2, ao3, ao0 };
                    for (unsigned int k = 0; k < 6; k++) {
                        glm::vec2 textureCoord = calculateTextureCoords(material, k, BlockFace::LEFT);
                        addVertex(vertices, x, y, z, BlockModel::NX_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::LEFT, ao[k]);
                    }
                }

                if (py) {
                    int ao0, ao1, ao2, ao3;
                    calculateAmbientOcclusion(worldX, worldY + 1, worldZ, 'Y', &ao0, &ao1, &ao2, &ao3);
                    int ao[6] = { ao0, ao1, ao2, ao2, ao3, ao0 };
                    for (unsigned int k = 0; k < 6; k++) {
                        glm::vec2 textureCoord = calculateTextureCoords(material, k, BlockFace::TOP);
                        addVertex(vertices, x, y, z, BlockModel::PY_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::TOP, ao[k]);
                    }
                }

                if (ny) {
                    int ao0, ao1, ao2, ao3;
                    calculateAmbientOcclusion(worldX, worldY - 1, worldZ, 'Y', &ao0, &ao1, &ao2, &ao3);
                    int ao[6] = { ao0, ao1, ao2, ao2, ao3, ao0 };
                    for (unsigned int k = 0; k < 6; k++) {
                        glm::vec2 textureCoord = calculateTextureCoords(material, k, BlockFace::BOTTOM);
                        addVertex(vertices, x, y, z, BlockModel::NY_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::BOTTOM, ao[k]);
                    }
                }

                if (pz) {
                    int ao0, ao1, ao2, ao3;
                    calculateAmbientOcclusion(worldX, worldY, worldZ + 1, 'Z', &ao0, &ao1, &ao2, &ao3);
                    int ao[6] = { ao0, ao1, ao2, ao2, ao3, ao0 };
                    for (unsigned int k = 0; k < 6; k++) {
                        glm::vec2 textureCoord = calculateTextureCoords(material, k, BlockFace::BACK);
                        addVertex(vertices, x, y, z, BlockModel::PZ_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::BACK, ao[k]);
                    }
                }

                if (nz) {
                    int ao0, ao1, ao2, ao3;
                    calculateAmbientOcclusion(worldX, worldY, worldZ - 1, 'Z', &ao0, &ao1, &ao2, &ao3);
                    int ao[6] = { ao0, ao1, ao2, ao2, ao3, ao0 };
                    for (unsigned int k = 0; k < 6; k++) {
                        glm::vec2 textureCoord = calculateTextureCoords(material, k, BlockFace::FRONT);
                        addVertex(vertices, x, y, z, BlockModel::NZ_POS[k], textureCoord, BlockModel::NORMALS[k], voxelID, BlockFace::FRONT, ao[k]);
                    }
                }
            }
        }
    }
    return vertices;
}

std::vector<Vertex> MeshBuilder::buildHandMesh() {
    std::vector<Vertex> vertices;
    std::vector<Vertex> vertexArray;

    vertexArray.push_back(Vertex{glm::vec3(0.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(10 * 4.0f / 64.0f, 12.0f / 64.0f)});
    vertexArray.push_back(Vertex{glm::vec3(0.2f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(9 * 4.0f / 64.0f, 12.0f / 64.0f)});
    vertexArray.push_back(Vertex{glm::vec3(0.2f,  0.0f, -1.0f), glm::vec3(0.0f), glm::vec2(9 * 4.0f / 64.0f, 0.0f)});
    vertexArray.push_back(Vertex{glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f), glm::vec2(10 * 4.0f / 64.0f, 0.0f)});

    vertexArray.push_back(Vertex{glm::vec3(0.2f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(11 * 4.0f / 64.0f, 12.0f / 64.0f)});
    vertexArray.push_back(Vertex{glm::vec3(0.2f, -1.0f, -1.2f), glm::vec3(0.0f), glm::vec2(10 * 4.0f / 64.0f, 12.0f / 64.0f)});
    vertexArray.push_back(Vertex{glm::vec3(0.2f,  0.0f, -1.2f), glm::vec3(0.0f), glm::vec2(10 * 4.0f / 64.0f, 0.0f)});
    vertexArray.push_back(Vertex{glm::vec3(0.2f,  0.0f, -1.0f), glm::vec3(0.0f), glm::vec2(11 * 4.0f / 64.0f, 0.0f)});

    for (int i = 0, index = 0; i < 4; i++) {
        vertices.push_back(vertexArray[index++]);
        vertices.push_back(vertexArray[index++]);
        vertices.push_back(vertexArray[index++]);
        vertices.push_back(vertexArray[index++]);
    }

    return vertices;
}

std::vector<float> MeshBuilder::buildWaterMesh(int chunkX, int chunkY, int chunkZ, int8_t* blocks) {
    std::vector<float> vertices;
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                int8_t blockId = blocks[x * CHUNK_AREA + y * CHUNK_SIZE + z];

                if (blockId == -1 || blockId != Material::WATER.getID()) continue;

                int worldX = x + chunkX * CHUNK_SIZE;
                int worldY = y + chunkY * CHUNK_SIZE;
                int worldZ = z + chunkZ * CHUNK_SIZE;

                bool px = isEmpty(worldX + 1, worldY, worldZ, 'W');
                bool nx = isEmpty(worldX - 1, worldY, worldZ, 'W');
                bool py = isEmpty(worldX, worldY + 1, worldZ, 'W');
                bool ny = isEmpty(worldX, worldY - 1, worldZ, 'W');
                bool pz = isEmpty(worldX, worldY, worldZ + 1, 'W');
                bool nz = isEmpty(worldX, worldY, worldZ - 1, 'W');

                if (px) {
                    for (int k = 0; k < 6; k++) {
                        addWaterVertex(vertices, x, y, z, BlockModel::PX_POS[k], BlockModel::TEXTURE_COORDS[k]);
                    }
                }

                if (nx) {
                    for (int k = 0; k < 6; k++) {
                        addWaterVertex(vertices, x, y, z, BlockModel::NX_POS[k], BlockModel::TEXTURE_COORDS[k]);
                    }
                }

                if (py) {
                    for (int k = 0; k < 6; k++) {
                        addWaterVertex(vertices, x, y, z, BlockModel::PY_POS[k], BlockModel::TEXTURE_COORDS[k]);
                    }
                }

                if (ny) {
                    for (int k = 0; k < 6; k++) {
                        addWaterVertex(vertices, x, y, z, BlockModel::NY_POS[k], BlockModel::TEXTURE_COORDS[k]);
                    }
                }

                if (pz) {
                    for (int k = 0; k < 6; k++) {
                        addWaterVertex(vertices, x, y, z, BlockModel::PZ_POS[k], BlockModel::TEXTURE_COORDS[k]);
                    }
                }

                if (nz) {
                    for (int k = 0; k < 6; k++) {
                        addWaterVertex(vertices, x, y, z, BlockModel::NZ_POS[k], BlockModel::TEXTURE_COORDS[k]);
                    }
                }
            }
        }
    }

    return vertices;
}

std::vector<float> MeshBuilder::buildQuadMesh(int8_t* blocks) {
    std::vector<float> vertices;
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {

                int8_t block = blocks[x * CHUNK_AREA + y * CHUNK_SIZE + z];
                Material material = Utils::getMaterialFromBlock(block);
                if (block == -1 || material.getType() != MaterialType::QUAD) continue;
                
                for (int k = 0; k < 6; k++) {
                    glm::vec2 textureCoords = calculateTextureCoords(Utils::getMaterialFromBlock(block), k, BlockFace::LEFT);
                    glm::vec3 vertex = QuadModel::PZ_POS[k];
                    vertices.push_back(vertex.x + x);
                    vertices.push_back(vertex.y + y);
                    vertices.push_back(vertex.z + z);
                    vertices.push_back(textureCoords.x);
                    vertices.push_back(textureCoords.y);
                    vertices.push_back(static_cast<float>(block));
                }

                for (int k = 0; k < 6; k++) {
                    glm::vec3 vertex = QuadModel::PX_POS[k];
                    glm::vec2 textureCoords = calculateTextureCoords(Utils::getMaterialFromBlock(block), k, BlockFace::LEFT);
                    vertices.push_back(vertex.x + x);
                    vertices.push_back(vertex.y + y);
                    vertices.push_back(vertex.z + z);
                    vertices.push_back(textureCoords.x);
                    vertices.push_back(textureCoords.y);
                    vertices.push_back(static_cast<float>(block));
                }
            }
        }
    }
    return vertices;
}
