#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "vertices.h"
#include "renderer.h"
#include "game.h"
#include "utils.h"

float angle = 0.0f;

Renderer::Renderer() {
    loadTextures();
    
    cursorShader = Shader("../assets/shaders/cursor.vert", "../assets/shaders/cursor.frag");
    chunkShader = Shader("../assets/shaders/chunk.vert", "../assets/shaders/chunk.frag");
    hotbarShader = Shader("../assets/shaders/hotbar.vert", "../assets/shaders/hotbar.frag");
    waterShader = Shader("../assets/shaders/water.vert", "../assets/shaders/water.frag");
    defaultShader = Shader("../assets/shaders/default.vert", "../assets/shaders/default.frag");
    hotbarIconShader = Shader("../assets/shaders/hotbaricon.vert", "../assets/shaders/hotbaricon.frag");
    doubleQuadShader = Shader("../assets/shaders/doublequad.vert", "../assets/shaders/doublequad.frag");
    blockSelectedMesh = SquareMesh(Point{0, 1}, 182.0f, 46.0f, 23.5f);
    cursorMesh = SquareMesh(Point{0, 0}, 11.0f, 11.0f, 11.0f);
}

void Renderer::loadTextures() {
    blockAtlas = Texture("../assets/textures/terrain.png");
    frameTexture = Texture("../assets/textures/frame.png");
    iconsTexture = Texture("../assets/textures/icons.png");
    skinTexture = Texture("../assets/textures/skin.png");
    crosshairTexture = Texture("../assets/textures/crosshair.png");
    hotbarTexture = Texture("../assets/textures/hotbar.png");
    blockIconAtlas = Texture("../assets/textures/blockIcons.png");
    waterDuDv = Texture("../assets/textures/water_dudv.png");
    waterTexture = Texture("../assets/textures/water.png");

    blockAtlas.load(); 
    frameTexture.load();
    iconsTexture.load();
    skinTexture.load();
    crosshairTexture.load();
    hotbarTexture.load();
    blockIconAtlas.load();
    waterDuDv.load();
    waterTexture.load();
}

void Renderer::drawVoxel(Camera& camera) {

    Player& player = Game::getInstance().getPlayer();
    Shader& shader = blockMesh.getShader();
    int8_t block = player.getRay().getBlock();
    Chunk* chunk = player.getRay().getChunk();

    if (block == -1 || chunk == nullptr) return;

    shader.enable();

    shader.setInt("uTexture", 2);
    shader.setFloat("scale", 1.025f);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, frameTexture.ID);

    camera.matrixVoxel(*chunk, player.getRay().blockX, player.getRay().blockY, player.getRay().blockZ, shader);

    blockMesh.drawElements();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::draw(Camera& camera, Chunk chunk, ChunkMesh chunkMesh) {

    Shader& shader = chunkShader;
    shader.enable();

    shader.setInt("uTexture", 0);
    shader.setFloat("elapsedTime", Game::getInstance().getElapsedTime());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, blockAtlas.ID);

    camera.matrix(chunk, shader, "cameraMatrix");
    chunkMesh.draw();

    DoubleQuadMesh* doubleQuadMesh = chunk.getDoubleQuadMesh();

    if (doubleQuadMesh != nullptr) {
        if (!doubleQuadMesh->isInitiated()) doubleQuadMesh->init();
        doubleQuadShader.enable();
        doubleQuadShader.setInt("uTexture", 0);
        doubleQuadShader.setFloat("elapsedTime", Game::getInstance().getElapsedTime());
        camera.matrixDoubleQuad(chunk, doubleQuadShader, "cameraMatrix");
        doubleQuadMesh->draw();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::drawWater(Camera& camera, Chunk chunk) {
    WaterMesh* waterMesh = chunk.getWaterMesh();

    if (waterMesh != nullptr) {
        if (!waterMesh->isInitiated()) waterMesh->init();
        glDisable(GL_CULL_FACE);
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_2D, waterTexture.ID);
        glActiveTexture(GL_TEXTURE8);
        glBindTexture(GL_TEXTURE_2D, waterDuDv.ID);
        waterShader.enable();
        waterShader.setInt("uTexture", 7);
        waterShader.setInt("uDudvTexture", 8);
        camera.matrixWater(chunk, waterShader, "cameraMatrix");
        waterMesh->draw();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::drawCursor(Camera& camera) {
    
    glDisable(GL_DEPTH_TEST);
    
    Shader& shader = cursorShader;
    shader.enable();

    shader.setInt("uTexture", 4);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, crosshairTexture.ID);

    camera.matrixCursor(shader, "cameraMatrix");

    cursorMesh.drawElements();

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::drawHand() {

    glDisable(GL_DEPTH_TEST);
    Shader& shader = handMesh.getShader();
    Game& game = Game::getInstance();
    Player& player = game.getPlayer();
    Hand& hand = player.getHand();
    ViewBobbing* viewBobbing = hand.getViewBobbing();

    shader.enable();

    shader.setInt("uTexture", 3);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, skinTexture.ID);

    glm::mat4 projection(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 model(1.0f);
    
    model = glm::translate(model, glm::vec3(-0.65f, 0.2f, 0.0f));

    model = glm::rotate(model, glm::radians(-80.0f), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0, 0, 1));
    model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(18.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-4.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-2.22f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(5.27f), glm::vec3(0.0f, 0.0f, 1.0f));
    
    model = glm::scale(model, glm::vec3(1.4f, 1.5f, 1.4f));

    model = glm::translate(model, glm::vec3(0.0f, viewBobbing->y, 0.0f));
    model = glm::translate(model, viewBobbing->position);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(projection * view * model));

    handMesh.drawElements();

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::drawHotbar(Hotbar hotbar) {
    Shader& shader = hotbarShader;

    shader.enable();
    shader.setInt("uTexture", 5);

    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, hotbarTexture.ID);

    glm::mat4 projection(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 model(1.0f);

    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(glm::radians(45.0f), (float) GameConfiguration::WINDOW_WIDTH / GameConfiguration::WINDOW_HEIGHT, 0.1f, 100.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.15f, 0.0f));
    model = glm::scale(model, glm::vec3(0.15f));

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(projection * view * model));
    
    hotbarMesh.drawElements();

    glBindTexture(GL_TEXTURE_2D, 0);
    this->drawHotbarBlocks(hotbar.getBlocks());

    model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(-0.525f + hotbar.getIndex() * .132f, -1.15f, 0.0f));
    model = glm::scale(model, glm::vec3(0.15f));

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, hotbarTexture.ID);

    shader = defaultShader;
    shader.enable();
    shader.setInt("uTexture", 5);
    
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(projection * view * model));
    blockSelectedMesh.drawElements();

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::drawHotbarBlocks(int8_t* blocks) {

    Shader& shader = hotbarIconShader;

    shader.enable();
    shader.setInt("uTexture", 6);

    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, blockIconAtlas.ID);

    float start = -0.525f;

    for (int i = 0; i < HOTBAR_SIZE; i++) {

        int8_t block = blocks[i];
        blockIconMesh.update(shader, block);

        glm::mat4 projection(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 model(1.0f);

        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        projection = glm::perspective(glm::radians(45.0f), (float) GameConfiguration::WINDOW_WIDTH / GameConfiguration::WINDOW_HEIGHT, 0.1f, 100.0f);
        model = glm::translate(model, glm::vec3(start + .132f * i, -1.15f, 0.0f));
        model = glm::scale(model, glm::vec3(.1f));

        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(projection * view * model));
        blockIconMesh.drawElements();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

BlockMesh& Renderer::getBlockMesh() {
    return blockMesh;
}