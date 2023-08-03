#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "vertices.h"
#include "renderer.h"

Renderer::Renderer() {
    loadTextures();
    cursorMesh = ImageMesh(0, 0, 16.0f);
}

void Renderer::loadTextures() {
    blockAtlas = Texture("../assets/textures/terrain.png");
    frameTexture = Texture("../assets/textures/frame.png");
    iconsTexture = Texture("../assets/textures/icons.png");

    blockAtlas.load();
    frameTexture.load();
    iconsTexture.load();
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

void Renderer::drawCursor() {
    
    Shader& shader = cursorMesh.getShader();

    shader.setInt("uTexture", 1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, iconsTexture.ID);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(projection * view * model));

    cursorMesh.drawElements();

    glBindTexture(GL_TEXTURE_2D, 0);
}

BlockMesh& Renderer::getBlockMesh() {
    return blockMesh;
}