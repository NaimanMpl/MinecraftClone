#version 330 core

out vec4 FragColor;
in vec2 textureCoord;
in float fresnel;

uniform sampler2D uTexture;
uniform sampler2D uDudvTexture;
uniform float elapsedTime;

const float waterStrength = 0.02;

void main() {
    
    vec2 distortion1 = (texture(uDudvTexture, vec2(textureCoord.x + elapsedTime, textureCoord.y)).rg * 2.0 - 1) * waterStrength;
    vec2 distortion2 = (texture(uDudvTexture, vec2(-textureCoord.x, textureCoord.y + elapsedTime)).rg * 2.0 - 1) * waterStrength;
    
    vec2 refractTexCoords = textureCoord;
    refractTexCoords += distortion1 + distortion2;
    refractTexCoords = clamp(refractTexCoords, 0.001, 0.999);
    
    vec4 refractionTexture = vec4(texture(uTexture, refractTexCoords).rgb * 0.6, 1.0);
    vec4 reflectionTexture = vec4(vec3(0.0, 0.0, 0.3), 0.3);
    FragColor = mix(refractionTexture, reflectionTexture, fresnel);
}