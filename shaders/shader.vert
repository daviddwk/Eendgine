#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 2) in vec2 aTexCoord;

out vec4 vertexColor;
out vec2 texCoord;

void main() {
    gl_Position = vec4(aPos, 1.0);
    vertexColor = aCol;
    texCoord = vec2(aTexCoord.x, -aTexCoord.y);
}
