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
        GLuint* vboID;
    public:

        Mesh();
        Mesh(Shader& shader, std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
        void drawElements();
        
        virtual void unload() = 0;
        virtual void draw() = 0;
        virtual void init() = 0;

        std::vector<GLuint>& getIndices();
        std::vector<Vertex>& getVertices();

        Shader& getShader();
};

#endif