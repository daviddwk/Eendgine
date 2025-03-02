#pragma once

#include <string>

#include <SDL2/SDL.h>

namespace Eendgine {

class Window {
    public:
        static void init(int width, int height, std::string name);
        static void close();
        static void swapBuffers();
        static void processInput();

    private:
        static void framebuffer_size_callback(SDL_Window* window, int width, int height);
        static void key_callback(SDL_Window* window, int key, int scancode, int action, int mods);
        inline static int _width = 0;
        inline static int _height = 0;
        inline static SDL_Window* _window = nullptr;
};
} // namespace Eendgine
