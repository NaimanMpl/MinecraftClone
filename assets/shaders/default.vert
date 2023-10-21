#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexture;

out vec2 textureCoord;

uniform mat4 cameraMatrix;

void main() {
    gl_Position = cameraMatrix * vec4(aPosition, 1.0);
    textureCoord = aTexture;
}