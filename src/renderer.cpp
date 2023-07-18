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

    shader.setInt("uTexture", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, block.getTextureID());

    blockMesh.draw();

    camera.matrix(block, shader, "cameraMatrix");

    glBindTexture(GL_TEXTURE_2D, 0);
}

BlockMesh& Renderer::getBlockMesh() {
    return blockMesh;
}