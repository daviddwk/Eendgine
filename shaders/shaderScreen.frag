#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D screenTexture;
uniform int height;
uniform int width;

void main()
{
        float dx = 10.0 * (1.0 / width);
        float dy = 10.0 * (1.0 / height);
        vec2 Coord = vec2(dx * floor(TexCoords.x / dx),
                          dy * floor(TexCoords.y / dy));
        FragColor = texture(screenTexture, Coord);
} 
