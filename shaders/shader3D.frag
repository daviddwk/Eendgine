#version 330 core
out vec4 FragColor;

in vec4 vertColor;
in vec2 vertUV;

uniform sampler2D texture0;

void main() {
    FragColor = texture(texture0, vertUV);
}
