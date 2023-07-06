#ifndef MESH_CLASS_H
#define MESS_CLASS_H

#include <glm/glm.hpp>
#include <vector>
#include "shader.h"
#include "buffers/EBO.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"

struct Texture {
    unsigned int id;
};

class Mesh {
    private:
        VAO VAO;
        void setup();
    public:

        static Mesh Block;

        std::vector<Vertex> vertices;
        std::vector <unsigned int> indices;
        std::vector<Texture> textures;

        Mesh();
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        Mesh Block();
        void draw(Shader& shader);
};

#endif