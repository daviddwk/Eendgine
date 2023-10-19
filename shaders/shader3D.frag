#version 330 core
out vec4 FragColor;

in vec4 vertColor;
in vec2 vertUV;

uniform sampler2D texture1;

void main() {
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);//texture(texture1, vertUV);
}
