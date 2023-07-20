#include "meshs/blockmesh.h"

BlockMesh::BlockMesh() {

    const glm::vec3 FRONT_NORMAL(0.0f, 0.0f, 1.0f);
    const glm::vec3 BACK_NORMAL(0.0f, 0.0f, -1.0f);
    const glm::vec3 LEFT_NORMAL(-1.0f, 0.0f, 0.0f);
    const glm::vec3 RIGHT_NORMAL(1.0f, 0.0f, 0.0f);
    const glm::vec3 TOP_NORMAL(0.0f, 1.0f, 0.0f);
    const glm::vec3 BOTTOM_NORMAL(0.0f, -1.0f, 0.0f);

    const glm::vec2 TEXCOORDS_TOP_LEFT(0.0f, 0.0f);
    const glm::vec2 TEXCOORDS_TOP_RIGHT(1.0f, 0.0f);
    const glm::vec2 TEXCOORDS_BOTTOM_RIGHT(1.0f, 1.0f);
    const glm::vec2 TEXCOORDS_BOTTOM_LEFT(0.0f, 1.0f);

    Vertex vertices[] = {

        // Face avant
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), FRONT_NORMAL, TEXCOORDS_BOTTOM_LEFT},
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), FRONT_NORMAL, TEXCOORDS_BOTTOM_RIGHT},
        Vertex{glm::vec3(0.5f, 0.5f, 0.5f), FRONT_NORMAL, TEXCOORDS_TOP_RIGHT},
        Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), FRONT_NORMAL, TEXCOORDS_TOP_LEFT},

        // Face arrière
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), BACK_NORMAL, TEXCOORDS_BOTTOM_LEFT},
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), BACK_NORMAL, TEXCOORDS_BOTTOM_RIGHT},
        Vertex{glm::vec3(0.5f, 0.5f, -0.5f), BACK_NORMAL, TEXCOORDS_TOP_RIGHT},
        Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), BACK_NORMAL, TEXCOORDS_TOP_LEFT},

        // Face gauche
        Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), LEFT_NORMAL, TEXCOORDS_BOTTOM_LEFT},
        Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), LEFT_NORMAL, TEXCOORDS_BOTTOM_RIGHT},
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), LEFT_NORMAL, TEXCOORDS_TOP_RIGHT},
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), LEFT_NORMAL, TEXCOORDS_TOP_LEFT},

        // Face droite
        Vertex{glm::vec3(0.5f, 0.5f, 0.5f), RIGHT_NORMAL, TEXCOORDS_BOTTOM_LEFT},
        Vertex{glm::vec3(0.5f, 0.5f, -0.5f), RIGHT_NORMAL, TEXCOORDS_BOTTOM_RIGHT},
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), RIGHT_NORMAL, TEXCOORDS_TOP_RIGHT},
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), RIGHT_NORMAL, TEXCOORDS_TOP_LEFT},

        // Face supérieure
        Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), TOP_NORMAL, TEXCOORDS_BOTTOM_LEFT},
        Vertex{glm::vec3(0.5f, 0.5f, 0.5f), TOP_NORMAL, TEXCOORDS_BOTTOM_RIGHT},
        Vertex{glm::vec3(0.5f, 0.5f, -0.5f), TOP_NORMAL, TEXCOORDS_TOP_RIGHT},
        Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), TOP_NORMAL, TEXCOORDS_TOP_LEFT},

        // Face inférieure
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), BOTTOM_NORMAL, TEXCOORDS_BOTTOM_LEFT},
        Vertex{glm::vec3(0.5f, -0.5f, 0.5f), BOTTOM_NORMAL, TEXCOORDS_BOTTOM_RIGHT},
        Vertex{glm::vec3(0.5f, -0.5f, -0.5f), BOTTOM_NORMAL, TEXCOORDS_TOP_RIGHT},
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), BOTTOM_NORMAL, TEXCOORDS_TOP_LEFT},
    };

    GLuint indices[] = {
        // Face avant
        0, 1, 2,
        2, 3, 0,

        // Face arrière
        4, 5, 6,
        6, 7, 4,

        // Face gauche
        8, 9, 10,
        10, 11, 8,

        // Face droite
        12, 13, 14,
        14, 15, 12,

        // Face supérieure
        16, 17, 18,
        18, 19, 16,

        // Face inférieure
        20, 21, 22,
        22, 23, 20
    };

    shader = Shader("../assets/shaders/cube.vert", "../assets/shaders/cube.frag");

    BlockMesh::vertices.insert(BlockMesh::vertices.begin(), std::begin(vertices), std::end(vertices));
    BlockMesh::indices.insert(BlockMesh::indices.begin(), std::begin(indices), std::end(indices));

    init();
}