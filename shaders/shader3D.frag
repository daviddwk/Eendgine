#version 330 core
out vec4 FragColor;

in vec4 vertColor;
in vec2 vertUV;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_diffuse1;

void main() {
    if(texture(texture_diffuse1, vertUV).x == 0){
        discard;
    }
    FragColor = texture(texture_diffuse0, vertUV);
}
