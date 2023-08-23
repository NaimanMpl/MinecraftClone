#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "vertices.h"
#include "renderer.h"
#include "game.h"

Renderer::Renderer() {
    loadTextures();
    loadSprites();
    Shader cursorShader("../assets/shaders/cursor.vert", "../assets/shaders/cursor.frag");
    cursorMesh = ImageMesh(0, 0, 16.0f, cursorShader);
}

void Renderer::loadTextures() {
    blockAtlas = Texture("../assets/textures/terrain.png");
    frameTexture = Texture("../assets/textures/frame.png");
    iconsTexture = Texture("../assets/textures/icons.png");

    blockAtlas.load();
    frameTexture.load();
    iconsTexture.load();
}

void Renderer::loadSprites() {
    blockSprite = Sprite{0, 0, 10, glm::vec2(0.0f, 15.0f), glm::vec2(16.0f, 16.0f)};
}

void Renderer::drawVoxel(Camera& camera) {

    Player& player = Game::getInstance().getPlayer();
    Shader& shader = blockMesh.getShader();
    Block* block = player.getRay().getBlock();
    Chunk* chunk = player.getRay().getChunk();

    if (block == nullptr || chunk == nullptr) return;

    shader.enable();

    shader.setInt("uTexture", 2);
    shader.setFloat("scale", 1.025f);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, frameTexture.ID);

    camera.matrixVoxel(*chunk, *block, shader);

    blockMesh.drawElements();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::drawVoxelBreak(Camera& camera) {

    Player& player = Game::getInstance().getPlayer();
    Shader& shader = blockMesh.getShader();
    Block* block = player.getRay().getBlock();
    Chunk* chunk = player.getRay().getChunk();

    if (block == nullptr || chunk == nullptr) return;

    shader.enable();
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Sprite), &blockSprite);

    shader.setInt("uTexture", 0);
    shader.setFloat("scale", 1.025f);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, blockAtlas.ID);

    camera.matrixVoxel(*chunk, *block, shader);

    blockMesh.drawElements();

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

void Renderer::drawCursor(Camera& camera) {
    
    glDisable(GL_DEPTH_TEST);
    
    Shader& shader = cursorMesh.getShader();
    shader.enable();

    shader.setInt("uTexture", 1);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, iconsTexture.ID);

    camera.matrixCursor(shader, "cameraMatrix");

    cursorMesh.drawElements();

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_DEPTH_TEST);
}

BlockMesh& Renderer::getBlockMesh() {
    return blockMesh;
}