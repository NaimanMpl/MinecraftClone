#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "block.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "buffers/EBO.h"
#include "vertices.h"

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

    Shader shader("../assets/shaders/cubeShader.glsl", "../assets/shaders/cubeFragment.glsl");
    std::string blockFaces[] = {
        "../assets/texture/stone.png",
        "../assets/texture/stone.png",
        "../assets/texture/stone.png",
        "../assets/texture/stone.png",
        "../assets/texture/stone.png"
    };

    Block block(blockFaces);

    VAO VAO1;
    VAO1.bind();

    VBO VBO1(BLOCK_VERTICES, sizeof(BLOCK_VERTICES));
    EBO EBO1(BLOCK_INDICES, sizeof(BLOCK_INDICES));

    VAO1.linkVBO(VBO1, 0);

    VAO1.unbind();   
    VBO1.unbind();
    EBO1.unbind();


    GLuint texture0Uniform = glGetUniformLocation(shader.ID, "uTexture");
    shader.enable();
    glUniform1i(texture0Uniform, 0);

    float rotation = 0.0f;
    double previousTime = glfwGetTime();

    GLuint uniformID = glGetUniformLocation(shader.ID, "scale");

    while (!glfwWindowShouldClose(window)) {
        

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shader.enable();
        glUniform1f(uniformID, 0.2f);
        double currentTime = glfwGetTime();

        if (currentTime - previousTime >= 1 / 60) {
            rotation += 0.05f;
            previousTime = currentTime;
        }

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        projection = glm::perspective(glm::radians(45.0f), (float) (WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);

        int modelLocation = glGetUniformLocation(shader.ID, "model");
        int viewLocation = glGetUniformLocation(shader.ID, "view");
        int projectionLocation = glGetUniformLocation(shader.ID, "projection");

        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

        block.bind();
        VAO1.bind();

        glActiveTexture(GL_TEXTURE0);
        glDrawElements(GL_TRIANGLES, sizeof(BLOCK_INDICES) / sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.destroy();
    VBO1.destroy();
    EBO1.destroy();
    shader.destroy();
    block.destroy();

    glfwTerminate();

    return 0;
}