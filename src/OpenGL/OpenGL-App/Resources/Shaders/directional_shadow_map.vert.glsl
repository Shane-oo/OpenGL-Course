#version 330

layout (location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 directionalLightSpaceTransform;


void main() {
    // lightSpaceTranform = project * view
    // converting into world space
    gl_Position = directionalLightSpaceTransform * model * vec4(pos, 1.0);
}