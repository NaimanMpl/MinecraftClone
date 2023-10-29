#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexture;
layout (location = 3) in float voxelID;
layout (location = 4) in float faceID;
layout (location = 5) in float aoID;

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
uniform float elapsedTime;

vec4 calculatePosition() {
    if (int(voxelID) != 9) return vec4(aPosition, 1.0);
    vec3 pos = aPosition.xyz;
    pos.x += sin((elapsedTime + pos.z + pos.y) * 1.8f) / 15.0f;
    pos.z -= cos((elapsedTime + pos.x + pos.y) * 1.8f) / 15.0f;
    return vec4(pos, 1.0);
}

void main() {
    gl_Position = cameraMatrix * calculatePosition();
    textureCoord = aTexture;
    normals = aNormals;
    material = voxelID;
    shading = faceShading[int(faceID)] * aoValues[int(aoID)];
    face = faceID;
}