#version 430 core
layout (location = 0) in vec3 aPos;

out vec4 fragColor; // Color passed to the fragment shader


uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 centerPos;

void main() {
    // Pass the position to the next shader stage (fragment shader)
    gl_Position = projection*view*model*vec4(centerPos+aPos, 1.0);
}