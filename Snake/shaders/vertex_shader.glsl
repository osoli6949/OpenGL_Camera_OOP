#version 420 core
layout (location = 0) in vec3 aPos; // position variable has attri pos 0
layout (location = 1) in vec2 aTexCoord; // texture variable has attri pos 1

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main () {
    gl_Position = projection * view * model * vec4(aPos, 1.0); // calculates MVP
    TexCoord = aTexCoord;
}