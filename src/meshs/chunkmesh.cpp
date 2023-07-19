#include "chunkmesh.h"

static const glm::vec3 NZ_POS[] = {
    glm::vec3(-0.5f,0.5f,-0.5f),
    glm::vec3(-0.5f,-0.5f,-0.5f),
    glm::vec3(0.5f,-0.5f,-0.5f),
    glm::vec3(0.5f,-0.5f,-0.5f),
    glm::vec3(0.5f,0.5f,-0.5f),
    glm::vec3(-0.5f,0.5f,-0.5f)
};

static const glm::vec2 TEXTURE_COORDS[] = {
    glm::vec2(0.0f, 0.0f),
    glm::vec2(0.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(1.0f, 0.0f),
    glm::vec2(0.0f, 0.0f)
};

static const glm::vec3 NORMALS[] = {
			
    glm::vec3(0.f, 0.f, 0.f),
    glm::vec3(0.f, 0.f, 0.f),
    glm::vec3(0.f, 0.f, 0.f),
    glm::vec3(0.f, 0.f, 0.f),
    glm::vec3(0.f, 0.f, 0.f),
    glm::vec3(0.f, 0.f, 0.f)
        
};
	

ChunkMesh::ChunkMesh() {
    shader = Shader("../assets/shaders/chunk.vert", "../assets/shaders/chunk.frag");
    
    glm::vec3 PX_POS[] = {
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
    };

    glm::vec3 NX_POS[] = {
        glm::vec3(-0.5f,0.5f,-0.5f),
        glm::vec3(-0.5f,-0.5f,-0.5f),
        glm::vec3(-0.5f,-0.5f,0.5f),
        glm::vec3(-0.5f,-0.5f,0.5f),
        glm::vec3(-0.5f,0.5f,0.5f),
        glm::vec3(-0.5f,0.5f,-0.5f)
	};

    glm::vec3 PY_POS[] = {
        glm::vec3(-0.5f,0.5f,0.5f),
        glm::vec3(-0.5f,0.5f,-0.5f),
        glm::vec3(0.5f,0.5f,-0.5f),
        glm::vec3(0.5f,0.5f,-0.5f),
        glm::vec3(0.5f,0.5f,0.5f),
        glm::vec3(-0.5f,0.5f,0.5f)
	};
}