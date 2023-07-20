#version 330 core

out vec4 FragColor;

const vec3 gamma = vec3(2.2);
const vec3 invGamma = 1 / gamma;

in vec2 textureCoord;
in vec3 normal;

uniform sampler2D uTexture;

void main() {
    FragColor = texture(uTexture, textureCoord);
}