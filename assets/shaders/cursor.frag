#version 330 core

out vec4 FragColor;

in vec2 textureCoord;

uniform sampler2D uTexture;

void main() {
    vec4 texColor = texture(uTexture, textureCoord);
    if (texColor.a == 0.0) {
        discard;
    }
    FragColor = texColor;
}