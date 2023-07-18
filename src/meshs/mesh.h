#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <glm/glm.hpp>
#include <vector>
#include "../shader.h"
#include "../buffers/EBO.h"
#include "../buffers/VAO.h"
#include "../buffers/VBO.h"
#include "../camera.h"

class Mesh {
    protected:
        Shader shader;
        std::vector<GLuint> indices;
        std::vector<Vertex> vertices;
        void init();
    private:
        VAO VAO;
    public:
        Mesh();
        void draw();

        std::vector<GLuint>& getIndices();
        std::vector<Vertex>& getVertices();

        Shader& getShader();
};

#endif