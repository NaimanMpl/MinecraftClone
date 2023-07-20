#version 330 core

out vec4 FragColor;

const vec3 gamma = vec3(2.2);
const vec3 invGamma = 1 / gamma;

in vec3 normals;
in vec2 textureCoord;

uniform sampler2D uTexture;

void main() {
    vec3 tex_col = texture(uTexture, textureCoord).rgb;
    FragColor = vec4(tex_col, 1);
}