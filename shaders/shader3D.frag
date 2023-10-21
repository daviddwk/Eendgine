#version 330 core
out vec4 FragColor;

in vec4 vertColor;
in vec2 vertUV;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_opacity;

void main() {
    if(texture(texture_diffuse, vertUV).xyz == vec3(1.0f, 0.0f, 1.0f)) {
        discard;
    }
    FragColor = texture(texture_diffuse, vertUV);
}
