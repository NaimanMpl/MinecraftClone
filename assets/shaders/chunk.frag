#version 330 core

out vec4 FragColor;

const vec3 gamma = vec3(2.2);
const vec3 invGamma = 1 / gamma;

in vec3 normals;
in vec2 textureCoord;
in vec3 voxelColor;
in float shading;
in float face;

uniform sampler2D uTexture;

void main() {
    vec3 tex = texture(uTexture, textureCoord).rgb;
    if (int(face) == 0) {
        tex.rgb *= vec3(0.5, 0.75, 0.4);
        /*
        tex = pow(tex, gamma);
        tex *= shading;
        tex = pow(tex, invGamma);
        */
    }
    tex *= shading;
    FragColor = vec4(tex, 1);
}