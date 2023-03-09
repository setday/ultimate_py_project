#version 330 core

layout(std140) uniform ObjectData {
    mat4 modelMatrix;
    mat4 invModelMatrix;
    bool hasInverse;
    vec3 vertex;
    int meshType;
} objects[];

uniform uint objectCount;

in vec2 verColor;

out vec4 color;

void main() {
}
