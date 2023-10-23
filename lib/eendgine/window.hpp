#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace Eendgine {

    class Window {
        public:
            static void init(int width, int height, std::string name);
            static void swapBuffers();
            static void pollEvents();
            inline static bool shouldClose = false;
        private:
            inline static int _width = 0;
            inline static int _height = 0;
            inline static SDL_Window* _window = nullptr;
    };

}
