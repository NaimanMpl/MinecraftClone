#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

enum BlockFace {
    TOP = 0,
    BOTTOM = 1,
    RIGHT = 2,
    LEFT = 3,
    BACK = 4,
    FRONT = 5
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    GLuint voxelID;
    GLuint faceID;
    GLuint aoID;
};

class VBO {
    public:
        GLuint ID;
        VBO();
        VBO(std::vector<Vertex>& vertices);
        VBO(std::vector<float>& vertices);

        void bind();
        void unbind();
        void destroy();

        GLuint* getID() {
            return &ID;
        }
};

#endif