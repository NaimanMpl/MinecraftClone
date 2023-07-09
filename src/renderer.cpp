#include "renderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "vertices.h"

Renderer::Renderer() {
    shader = Shader("../assets/shaders/cubeShader.glsl", "../assets/shaders/cubeFragment.glsl");
}

Shader Renderer::getShader() {
    return shader;
}

void Renderer::draw(Camera camera, Block block) {

    shader.enable();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, block.getTextureID());
    glUniform1i(glGetUniformLocation(shader.ID, "uTexture"), 0);
    
    camera.matrix(block, shader, "cameraMatrix");

    glDrawElements(GL_TRIANGLES, blockMesh.getIndices().size(), GL_UNSIGNED_INT, 0);
}