#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>
#include <vector>
#include "shader.h"
#include "texture.h"
#include "block.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "buffers/EBO.h"
#include "renderer.h"

// Dimensions de la fenêtre
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Callback pour gérer le redimensionnement de la fenêtre
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Erreur lors de l'initialisation de GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Minecraft", nullptr, nullptr);
    if (!window) {
        std::cerr << "Erreur lors de la création de la fenêtre GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Erreur lors de l'initialisation de Glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    Texture stoneTexture("../assets/textures/stone.png");
    stoneTexture.load();

    glm::vec3 blockPos = glm::vec3(0.0f, -0.5f, -2.0f);
    glm::vec3 blockPos1 = glm::vec3(0.3f, -0.8f, -2.0f);

    Block stoneBlock(stoneTexture.ID, blockPos);
    Block stoneBlock2(stoneTexture.ID, blockPos1);

    Renderer& renderer = Renderer::getInstance();

    VAO VAO = renderer.getBlockVAO();
    VBO blockVBO = renderer.getBlockVBO();
    EBO blockEBO = renderer.getBlockEBO();
    Shader shader = renderer.getShader();

    float rotation = 0.0f;
    double previousTime = glfwGetTime();

    GLuint uniformID = glGetUniformLocation(shader.ID, "scale");

    glEnable(GL_DEPTH_TEST);

    std::vector<Block> blocks;

    blocks.push_back(stoneBlock);
    blocks.push_back(stoneBlock2);

    while (!glfwWindowShouldClose(window)) {
        

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.enable();
        glUniform1f(uniformID, 0.2f);
        double currentTime = glfwGetTime();

        for (const Block& block : blocks) {
            renderer.draw(block);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO.destroy();
    blockVBO.destroy();
    blockEBO.destroy();
    stoneTexture.destroy();
    shader.destroy();

    glfwTerminate();

    return 0;
}