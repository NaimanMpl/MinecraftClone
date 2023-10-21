#version 330 core

layout (location = 0) in vec2 aPosition;
layout (location = 1) in float vertexID;

out vec2 textureCoord;

uniform mat4 cameraMatrix;
uniform vec2 aTexture[4];

void main() {
    gl_Position = cameraMatrix * vec4(aPosition, 0.0, 1.0);
    textureCoord = aTexture[int(vertexID)];
}