#pragma once

struct Position {
    float x;
    float y;
    float z;
};

struct Color {
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;
};

struct UV {
    float u;
    float v;
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

