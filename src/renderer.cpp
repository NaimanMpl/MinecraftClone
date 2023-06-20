#include "renderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "vertices.h"

Renderer::Renderer() {
    shader = Shader("../assets/shaders/cubeShader.glsl", "../assets/shaders/cubeFragment.glsl");
    shader.enable();
    blockVBO = VBO(Vertices::BLOCK_VERTICES, sizeof(Vertices::BLOCK_VERTICES));
    blockEBO = EBO(Vertices::BLOCK_INDICES, sizeof(Vertices::BLOCK_INDICES));
    
}

Shader Renderer::getShader() {
    return shader;
}

void Renderer::draw(Camera camera, Block block) {

    VAO VAO = block.getVAO();

    VAO.bind();
    blockVBO.bind();
    blockEBO.bind();

    VAO.linkAttrib(blockVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    VAO.linkAttrib(blockVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    
    shader.enable();
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, block.getTextureID());
    glUniform1i(glGetUniformLocation(shader.ID, "uTexture"), 0);
    
    camera.matrix(block, 45.0f, 0.1f, 100.0f, shader, "cameraMatrix");

    glDrawElements(GL_TRIANGLES, sizeof(Vertices::BLOCK_INDICES) / sizeof(int), GL_UNSIGNED_INT, 0);

}