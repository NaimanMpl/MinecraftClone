#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexture;
layout (location = 2) in float voxelID;

out vec2 textureCoord;
out float material;

uniform mat4 cameraMatrix;
uniform float elapsedTime;

vec4 calculatePosition() {
    vec3 pos = aPosition.xyz;
    pos.x += sin((elapsedTime + pos.z + pos.y) * 1.8f) / 15.0f;
    pos.z -= cos((elapsedTime + pos.x + pos.y) * 1.8f) / 15.0f;
    return vec4(pos, 1.0);
}

void main() {
    gl_Position = cameraMatrix * calculatePosition();
    textureCoord = aTexture;
    material = voxelID;
}