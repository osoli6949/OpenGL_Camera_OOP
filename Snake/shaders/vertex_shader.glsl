#version 420 core
layout (location = 0) in vec3 aPos; // position variable has attri pos 0

void main () {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
