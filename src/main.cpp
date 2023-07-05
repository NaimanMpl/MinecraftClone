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
#include "block.h"
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
    Renderer& renderer = Renderer::getInstance();
    Shader shader = renderer.getShader();

    game.init();

    Camera& camera = game.getCamera();
    
    GLuint uniformID = glGetUniformLocation(shader.ID, "scale");

    glEnable(GL_DEPTH_TEST);
    
    float previousTime = (float) glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        
        float currentTime = (float) glfwGetTime();
        float deltaTime = currentTime - previousTime;

        previousTime = currentTime;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.enable();
        glUniform1f(uniformID, 0.3f);
        
        game.render(renderer);
        
        game.update();

        camera.inputs(window, deltaTime);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    game.quit();
    shader.destroy();

    glfwTerminate();

    return 0;
}