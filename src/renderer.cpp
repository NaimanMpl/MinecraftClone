#include "renderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Vertices {
    GLfloat BLOCK_VERTICES[] = {
        // Face avant
        -0.5f, -0.5f, 0.5f,    0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,     1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,      1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,     0.0f, 1.0f,

        // Face arrière
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
        0.5f, 0.5f, -0.5f,     0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f,    1.0f, 1.0f,

        // Face gauche
        -0.5f, 0.5f, 0.5f,     1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,    0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,    1.0f, 1.0f,

        // Face droite
        0.5f, 0.5f, 0.5f,      0.0f, 0.0f,
        0.5f, 0.5f, -0.5f,     1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,    1.0f, 1.0f,
        0.5f, -0.5f, 0.5f,     0.0f, 1.0f,

        // Face supérieure
        -0.5f, 0.5f, 0.5f,     0.0f, 1.0f,
        0.5f, 0.5f, 0.5f,      1.0f, 1.0f,
        0.5f, 0.5f, -0.5f,     1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,    0.0f, 0.0f,

        // Face inférieure
        -0.5f, -0.5f, 0.5f,    0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,     1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,    1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f
    };

    GLuint BLOCK_INDICES[] = {
        // Face avant
        0, 1, 2,
        2, 3, 0,

        // Face arrière
        4, 5, 6,
        6, 7, 4,

        // Face gauche
        8, 9, 10,
        10, 11, 8,

        // Face droite
        12, 13, 14,
        14, 15, 12,

        // Face supérieure
        16, 17, 18,
        18, 19, 16,

        // Face inférieure
        20, 21, 22,
        22, 23, 20
    };

    GLfloat BLOCK_TEXTURE_COORDS[] = {
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    };
}

Renderer::Renderer() {
    shader = Shader("../assets/shaders/cubeShader.glsl", "../assets/shaders/cubeFragment.glsl");
    shader.enable();
    blockVAO.bind();
    blockVBO = VBO(Vertices::BLOCK_VERTICES, sizeof(Vertices::BLOCK_VERTICES));
    blockEBO = EBO(Vertices::BLOCK_INDICES, sizeof(Vertices::BLOCK_INDICES));
    blockVAO.linkAttrib(blockVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    blockVAO.linkAttrib(blockVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));
}

VBO Renderer::getBlockVBO() {
    return blockVBO;
}

EBO Renderer::getBlockEBO() {
    return blockEBO;
}

VAO Renderer::getBlockVAO() {
    return blockVAO;
}

Shader Renderer::getShader() {
    return shader;
}

void Renderer::draw(Block block) {

    blockVAO.bind();
    blockVBO.bind();
    blockEBO.bind();

    shader.enable();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, block.getTextureID());
    glUniform1i(glGetUniformLocation(shader.ID, "uTexture"), 0);

    int modelLocation = glGetUniformLocation(shader.ID, "model");
    int viewLocation = glGetUniformLocation(shader.ID, "view");
    int projectionLocation = glGetUniformLocation(shader.ID, "projection");

    glm::mat4 model = block.getModel();
    glm::mat4 view = block.getView();
    glm::mat4 projection = block.getProjection();

    model = glm::rotate(model, glm::radians(0.05f), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
    projection = glm::perspective(glm::radians(45.0f), (float) (800 / 800), 0.1f, 100.0f);

    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

    glDrawElements(GL_TRIANGLES, sizeof(Vertices::BLOCK_INDICES) / sizeof(int), GL_UNSIGNED_INT, 0);

}