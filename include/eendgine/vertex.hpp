#pragma once

struct Position {
    float x = 0;
    float y = 0;
    float z = 0;
};

struct Color {
    unsigned int r = 0;
    unsigned int g = 0;
    unsigned int b = 0;
    unsigned int a = 0;
};

struct UV {
    float u = 0;
    float v = 0;
};

struct Vertex {
    Position position;
    Color color;
    UV uv;
    
    void setPosition(float x, float y, float z) {
        position.x = x;
        position.y = y;
        position.z = z;
    }

    void setColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }

    void setUv(float u, float v) {
        uv.u = u;
        uv.v = v;
    }
};

