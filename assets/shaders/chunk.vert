#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexture;
layout (location = 3) in int voxelID;
layout (location = 4) in int faceID;
layout (location = 5) in int aoID;

out vec2 textureCoord;
out vec3 normals;
out float material;
out float shading;
out float face;

const float aoValues[4] = float[4](0.1, 0.25, 0.5, 1.0);

const float faceShading[6] = float[6](
    1.0, 0.5,
    0.5, 0.8,
    0.5, 0.8
);

uniform mat4 cameraMatrix;

void main() {
    gl_Position = cameraMatrix * vec4(aPosition, 1.0);
    textureCoord = aTexture;
    normals = aNormals;
    material = voxelID;
    shading = faceShading[faceID] * aoValues[aoID];
    face = faceID;
}