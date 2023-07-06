#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class VBO {
    public:
        GLuint ID;
        VBO();
        VBO(std::vector<Vertex>& vertices);

        void bind();
        void unbind();
        void destroy();
};

#endif