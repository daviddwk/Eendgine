#version 330 core
out vec4 FragColor;

in vec4 vertColor;
in vec2 vertUV;

uniform sampler2D ourTexture;

void main() {
    if(texture(ourTexture, vertUV).xyz == vec3(1.0f, 0.0f, 1.0f)) {
        discard;
    }
    FragColor = texture(ourTexture, vertUV);
}
