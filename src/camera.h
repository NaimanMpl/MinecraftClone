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

class Camera {
    private:
        glm::vec3 position;
        glm::vec3 orientation;
        glm::vec3 up;

        int width, height;

        float speed, sensitivity;

    public:
        Camera();
        Camera(int width, int height, glm::vec3 position);
        void matrix(float fovDeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
        void inputs(GLFWwindow* window);
};

#endif