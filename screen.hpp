#pragma once
#include "shader.hpp"

#include <SDL2/SDL.h>
#include <string>

namespace Eendgine {

class Screen {
    public:
        static void construct(int width, int height);
        static void destruct();
        static Screen& get();

        void bind();
        void render(ShaderProgram shader);

    private:
        Screen(int width, int height);
        ~Screen();

        inline static Screen* _instance = nullptr;

        int _width = 0;
        int _height = 0;
        unsigned int _VAO = 0;
        unsigned int _VBO = 0;
        unsigned int _RBO = 0;
        unsigned int _FB = 0;
        unsigned int _textureColorBuffer = 0;
        float _screenTriVerts[12] = {
            -1.0f,
            3.0f,
            0.0f,
            2.0f,
            -1.0f,
            -1.0f,
            0.0f,
            0.0f,
            3.0f,
            -1.0f,
            2.0f,
            0.0f,
        };
};

} // namespace Eendgine
