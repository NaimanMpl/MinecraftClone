#version 330 core

out vec4 FragColor;

const vec3 gamma = vec3(2.2);
const vec3 invGamma = 1 / gamma;

in vec3 normals;
in vec2 textureCoord;
in vec3 voxelColor;
in float shading;
in float face;
in float material;

uniform sampler2D uTexture;

void main() {
    if (texture(uTexture, textureCoord).a <= 0) discard;
    vec3 tex = texture(uTexture, textureCoord).rgb;
    if (int(face) == 0 && int(material) == 3) {
        tex.rgb *= vec3(0.5, 0.75, 0.4);
        /*
        tex = pow(tex, gamma);
        tex *= shading;
        tex = pow(tex, invGamma);
        */
    }
    tex *= shading;
    float alpha = int(material) == 205 ? 0.8 : 1;
    FragColor = vec4(tex, alpha);
}