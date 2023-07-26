#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "vertices.h"
#include "renderer.h"

Renderer::Renderer() {
    loadTextures();
}

void Renderer::loadTextures() {
    blockAtlas = Texture("../assets/textures/terrain.png");
    frameTexture = Texture("../assets/textures/frame.png");

    blockAtlas.load();
    frameTexture.load();
}

void Renderer::draw(Camera camera, Block block) {

    Shader& shader = blockMesh.getShader();
    shader.enable();

    shader.setInt("uTexture", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    blockMesh.draw();

    camera.matrix(block, shader, "cameraMatrix");

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::draw(Camera& camera, Chunk chunk, ChunkMesh chunkMesh) {

    Shader& shader = chunkMesh.getShader();
    shader.enable();

    shader.setInt("uTexture", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, blockAtlas.ID);

    camera.matrix(chunk, shader, "cameraMatrix");

    chunkMesh.draw();

    glBindTexture(GL_TEXTURE_2D, 0);
}

BlockMesh& Renderer::getBlockMesh() {
    return blockMesh;
}