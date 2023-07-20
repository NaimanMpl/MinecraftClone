#include "meshs/chunkmesh.h"

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
    VAO.linkAttrib(VBO, 3, 1, GL_FLOAT, sizeof(Vertex), (void*) (8 * sizeof(float))); // voxelID

    VAO.unbind();
    VBO.unbind();
}

void ChunkMesh::update(Chunk chunk) {
    this->chunk = chunk;
    buildMesh();
}

void ChunkMesh::buildMesh() {
    std::vector<Block>& blocks = chunk.getBlocks();
    for (int i = 0; i < blocks.size(); i++) {
        Block block = blocks.at(i);
        // Those bools represents what cube faces we should draw based on different axes
        bool px = false, nx = false, py = false, ny = false, pz = false, nz = false;
        for (int j = 0; j < blocks.size(); j++) {
            Block otherBlock = blocks.at(j);

            // Collision on X axis
            bool rightCollision = block.getX() + 1 == otherBlock.getX();
            bool leftCollision = block.getX() - 1 == otherBlock.getX();
            
            // Collision on Y axis
            bool upCollision = block.getY() + 1 == otherBlock.getY();
            bool downCollision = block.getY() - 1 == otherBlock.getY();

            // Collision on Z axis
            bool forwardCollision = block.getZ() + 1 == otherBlock.getZ();
            bool backwardCollision = block.getZ() - 1 == otherBlock.getZ();

            bool sameX = block.getX() == otherBlock.getX();
            bool sameY = block.getY() == otherBlock.getY();
            bool sameZ = block.getZ() == otherBlock.getZ();
            
            if (rightCollision && sameY && sameZ) px = true;
            if (leftCollision && sameY && sameZ) nx = true;
            if (sameX && upCollision && sameZ) py = true;
            if (sameX && downCollision && sameY) ny = true;
            if (sameX && sameY && forwardCollision) pz = true;
            if (sameX && sameZ && backwardCollision) nz = true;
        }

        // Adding visibile faces to the chunk mesh
        glm::vec3 blockVector(block.getX(), block.getY(), block.getZ());

        if (!px) {
            for (unsigned int k = 0; k < 6; k++) {
                vertices.push_back(Vertex{
                    glm::vec3(BlockModel::PX_POS[k] + blockVector),
                    BlockModel::NORMALS[k],
                    BlockModel::TEXTURE_COORDS[k],
                    (GLuint) (block.getX() + block.getY() + block.getZ())
                });
            }
        }

        if (!nx) {
            for (unsigned int k = 0; k < 6; k++) {
                vertices.push_back(Vertex{
                    glm::vec3(BlockModel::NX_POS[k] + blockVector),
                    BlockModel::NORMALS[k],
                    BlockModel::TEXTURE_COORDS[k],
                    (GLuint) (block.getX() + block.getY() + block.getZ())
                });
            }
        }

        if (!py) {
            for (unsigned int k = 0; k < 6; k++) {
                vertices.push_back(Vertex{
                    glm::vec3(BlockModel::PY_POS[k] + blockVector),
                    BlockModel::NORMALS[k],
                    BlockModel::TEXTURE_COORDS[k],
                    (GLuint) (block.getX() + block.getY() + block.getZ())
                });
            }
        }

        if (!ny) {
            for (unsigned int k = 0; k < 6; k++) {
                vertices.push_back(Vertex{
                    glm::vec3(BlockModel::NY_POS[k] + blockVector),
                    BlockModel::NORMALS[k],
                    BlockModel::TEXTURE_COORDS[k],
                    (GLuint) (block.getX() + block.getY() + block.getZ())
                });
            }
        }

        if (!pz) {
            for (unsigned int k = 0; k < 6; k++) {
                vertices.push_back(Vertex{
                    glm::vec3(BlockModel::PZ_POS[k] + blockVector),
                    BlockModel::NORMALS[k],
                    BlockModel::TEXTURE_COORDS[k],
                    (GLuint) (block.getX() + block.getY() + block.getZ())
                });
            }
        }

        if (!nz) {
            for (unsigned int k = 0; k < 6; k++) {
                vertices.push_back(Vertex{
                    glm::vec3(BlockModel::NZ_POS[k] + blockVector),
                    BlockModel::NORMALS[k],
                    BlockModel::TEXTURE_COORDS[k],
                    (GLuint) (block.getX() + block.getY() + block.getZ())
                });
            }
        }
    }
}

void ChunkMesh::populate() {

}