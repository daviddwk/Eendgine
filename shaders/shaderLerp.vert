#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNexPos;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aUV;
layout (location = 4) in vec3 aNormal;
layout (location = 5) in vec3 aNexNormal;

uniform float lerp;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;

out vec2 vertUV;
out vec4 vertColor;

void main() {
    vec3 lerpPos = (lerp * aNexPos) + ((1.0f - lerp) * aPos);
    // do lerp normal similarly if you want to use it
    gl_Position = projection * view * transform * vec4(lerpPos, 1.0f);
    vertColor = aColor;
    vertUV = vec2(aUV.x, -aUV.y);
}
