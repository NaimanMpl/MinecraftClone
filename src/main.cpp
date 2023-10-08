#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>
#include <vector>
#include <chrono>
#include "shader.h"
#include "texture.h"
#include "world/block.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "buffers/EBO.h"
#include "renderer.h"
#include "game.h"
#include "game_configuration.h"

int main() {
    if (!glfwInit()) {
        std::cerr << "Erreur lors de l'initialisation de GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(GameConfiguration::WINDOW_WIDTH, GameConfiguration::WINDOW_HEIGHT, "Minecraft", nullptr, nullptr);
    if (!window) {
        std::cerr << "Erreur lors de la création de la fenêtre GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Erreur lors de l'initialisation de Glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    Game& game = Game::getInstance();
    game.init();

    Renderer& renderer = Renderer::getInstance();
    Camera& camera = game.getCamera();
    Player& player = game.getPlayer();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    float previousTime = (float) glfwGetTime();
    float deltaTime = 0.0f;
    bool firstMouse = true;
    double previousFPSTime = glfwGetTime();
    int frames = 0;
    while (!glfwWindowShouldClose(window)) {
        
        float currentTime = (float) glfwGetTime();
        double currentFPSTime = glfwGetTime();
        deltaTime = currentTime - previousTime;

        frames++;

        previousTime = currentTime;

        if (currentFPSTime - previousFPSTime >= 1.0) {
            // std::cout << "FPS : " << frames << std::endl;
            frames = 0;
            previousFPSTime = currentFPSTime;
        }

        glClearColor(0.58f, 0.83f, 0.99f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        player.handleInputs(window, deltaTime);

        game.update(deltaTime);
        game.render(renderer);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    game.quit();

    renderer.getBlockMesh().getShader().destroy();

    glfwTerminate();

    return 0;
}