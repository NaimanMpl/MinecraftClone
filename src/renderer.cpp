#include "renderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "vertices.h"

Renderer::Renderer() {
    shader = Shader("../assets/shaders/cubeShader.glsl", "../assets/shaders/cubeFragment.glsl");
    shader.enable();
}

Shader Renderer::getShader() {
    return shader;
}

void Renderer::draw(Block block) {

    VAO VAO = block.getVAO();
    VBO VBO = block.getVBO();
    EBO EBO = block.getEBO();

    VAO.bind();
    VBO.bind();
    EBO.bind();

    VAO.linkAttrib(VBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    VAO.linkAttrib(VBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    
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