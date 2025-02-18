#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;

uniform mat4 cameraMatrix;
uniform float scale;

out vec2 textureCoord;

void main() {
    gl_Position = cameraMatrix * vec4(aPosition, 1.0);
    textureCoord = aTexture;
}