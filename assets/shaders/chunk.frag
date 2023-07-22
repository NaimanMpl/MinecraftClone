#version 330 core

out vec4 FragColor;

const vec3 gamma = vec3(2.2);
const vec3 invGamma = 1 / gamma;

in vec3 normals;
in vec2 textureCoord;
in vec3 voxelColor;

uniform sampler2D uTexture;

void main() {
    vec3 tex = texture(uTexture, textureCoord).rgb;
    tex = pow(tex, gamma);
    tex.rgb *= voxelColor;
    tex = pow(tex, invGamma);
    FragColor = vec4(tex, 1);
}