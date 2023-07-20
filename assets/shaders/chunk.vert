#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexture;

out vec2 textureCoord;
out vec3 normals;

uniform mat4 cameraMatrix;

void main() {
    gl_Position = cameraMatrix * vec4(aPosition, 1.0);
    textureCoord = aTexture;
    normals = aNormals;
}