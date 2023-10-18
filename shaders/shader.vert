#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aNormal;

out vec4 vertColor;
out vec2 vertUV;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(aPos, 1.0f);
    vertColor = aCol;
    vertUV = vec2(aUV.x, -aUV.y);
}
