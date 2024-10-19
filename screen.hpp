#pragma once
#include "shader.hpp"

#include <SDL2/SDL.h>
#include <string>

namespace Eendgine {

class Screen {
  public:
    static void init(int width, int height);
    static void close();
    static void bind();
    static void render(ShaderProgram shader);

  private:
    inline static int _width = 0;
    inline static int _height = 0;
    inline static unsigned int _VAO = 0;
    inline static unsigned int _VBO = 0;
    inline static unsigned int _RBO = 0;
    inline static unsigned int _FB = 0;
    inline static unsigned int _textureColorBuffer = 0;
    inline static float _screenTriVerts[] = {
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
