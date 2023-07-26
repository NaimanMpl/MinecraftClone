#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexture;
layout (location = 3) in int voxelID;
layout (location = 4) in int faceID;

out vec2 textureCoord;
out vec3 normals;
out vec3 voxelColor;
out float shading;

const float faceShading[6] = float[6](
    1.0, 0.5,
    0.5, 0.8,
    0.5, 0.8
);

uniform mat4 cameraMatrix;

vec3 hash31(float p) {
    vec3 p3 = fract(vec3(p * 21.2) * vec3(0.1031, 0.1030, 0.0973));
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.xxy + p3.yzz) * p3.zyx) + 0.05;
}

void main() {
    gl_Position = cameraMatrix * vec4(aPosition, 1.0);
    textureCoord = aTexture;
    normals = aNormals;
    voxelColor = hash31(voxelID);
    shading = faceShading[faceID];
}