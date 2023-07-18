#include "renderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "vertices.h"

Renderer::Renderer() {
    
}

void Renderer::draw(Camera camera, Block block) {

    Shader& shader = blockMesh.getShader();
    shader.enable();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, block.getTextureID());

    camera.matrix(block, shader, "cameraMatrix");

    blockMesh.draw();

    glBindTexture(GL_TEXTURE_2D, 0);
}

BlockMesh& Renderer::getBlockMesh() {
    return blockMesh;
}