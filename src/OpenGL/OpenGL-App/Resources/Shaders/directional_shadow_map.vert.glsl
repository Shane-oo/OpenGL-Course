#version 330

layout (location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 directionalLightTransform;


void main() {
    // lightSpaceTranform = project * view
    // converting into world space
    gl_Position = directionalLightTransform * model * vec4(pos, 1.0);
}