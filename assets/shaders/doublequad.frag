#version 330 core

out vec4 FragColor;
in vec2 textureCoord;
in float material;

uniform sampler2D uTexture;

void main() {
    if (texture(uTexture, textureCoord).a <= 0) discard;
    vec3 tex = texture(uTexture, textureCoord).rgb;
    if (int(material) == 13) {
        tex.rgb *= vec3(0.5, 0.75, 0.4);
    }
    FragColor = vec4(tex, 1.0);
}