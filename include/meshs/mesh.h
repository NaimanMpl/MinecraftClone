#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <glm/glm.hpp>
#include <vector>
#include "../shader.h"
#include "../buffers/EBO.h"
#include "../buffers/VAO.h"
#include "../buffers/VBO.h"

class Mesh {
    protected:
        Shader shader;
        std::vector<GLuint> indices;
        std::vector<Vertex> vertices;
        VAO VAO;
        void init();
    public:

        Mesh();
        Mesh(Shader& shader, std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
        void draw();
        void drawElements();

        std::vector<GLuint>& getIndices();
        std::vector<Vertex>& getVertices();

        Shader& getShader();
};

#endif