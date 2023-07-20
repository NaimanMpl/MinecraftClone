#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shader.h"
#include "block.h"
#include "chunk.h"

class Camera {
    private:
        glm::vec3 position;
        glm::vec3 orientation;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 front;

        int width, height;

        float speed, sensitivity, horizontalAngle, verticalAngle, yaw, pitch, fov, nearPlane, farPlane;

        float mouseX, mouseY, lastMouseX, lastMouseY, mouseOffsetX, mouseOffsetY;
        bool firstMouse;

    public:
        Camera();
        Camera(int width, int height, glm::vec3 position);
        void matrix(Block block, Shader& shader, const char* uniform);
        void matrix(Chunk chunk, Shader& shader, const char* uniform);
        void inputs(GLFWwindow* window, float deltaTime);
};

#endif