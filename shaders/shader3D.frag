#version 330 core
out vec4 FragColor;

in vec4 vertColor;
in vec2 vertUV;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_opacity;

void main() {
    if(texture(texture_opacity, vertUV).x == 0){
        discard;
    }
    FragColor = texture(texture_diffuse, vertUV);
}
