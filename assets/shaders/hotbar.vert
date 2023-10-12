#version 330 core

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aTexture;

out vec2 textureCoord;

uniform mat4 cameraMatrix;

void main() {
    gl_Position = cameraMatrix * vec4(aPosition.x, aPosition.y, 0.0, 1.0);
    textureCoord = aTexture;
}