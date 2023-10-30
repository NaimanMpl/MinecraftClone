#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexture;

out vec2 textureCoord;
out float fresnel;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 cameraPosition;
uniform float elapsedTime;

vec4 calculatePosition(vec3 worldPosition) {
    vec3 pos = aPosition.xyz;
    float waveHeight = sin(worldPosition.x + elapsedTime) * sin(worldPosition.z + elapsedTime) * 0.1;
    pos.y += waveHeight;
    return vec4(pos, 1.0);
}

void main() {
    vec4 worldPosition = model * vec4(aPosition, 1.0);
    vec3 toCameraVector = cameraPosition - worldPosition.xyz;
    vec3 viewVector = normalize(toCameraVector);
    fresnel = dot(viewVector, vec3(0.0, 1.0, 0.0));
    gl_Position = projection * view * model * calculatePosition(worldPosition.xyz);
    textureCoord = aTexture;
}