#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aNormal;

uniform mat4 view;
uniform mat4 projection;

out vec2 vertUV;
out vec4 vertColor;

void main() {
    gl_Position = projection * view * vec4(aPos, 1.0f);
    vertColor = aColor;
    vertUV = vec2(aUV.x, aUV.y);
}
