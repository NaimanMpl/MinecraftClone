#version 330 core

out vec4 FragColor;

const vec3 gamma = vec3(2.2);
const vec3 invGamma = 1 / gamma;

in vec3 normals;
in vec2 textureCoord;
in vec3 voxelColor;

uniform sampler2D uTexture;

void main() {
    FragColor = vec4(voxelColor, 1);
}