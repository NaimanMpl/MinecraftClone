#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <glm/glm.hpp>
#include <vector>
#include "shader.h"
#include "buffers/EBO.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "camera.h"

class Mesh {
    protected:
        GLuint textureID;
        std::vector<GLuint> indices;
        std::vector<Vertex> vertices;
    private:
        VAO VAO;

    public:
        static const Mesh block;

        Mesh();
        void init();

        std::vector<GLuint>& getIndices();
        std::vector<Vertex>& getVertices();
};

#endif