#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace Eendgine {

    class Window {
        public:
            Window();
            ~Window();

            void init(int width, int height, std::string name);
            void swapBuffers();
            void pollEvents();

            bool shouldClose = false;
        private:
            int _width = 0;
            int _height = 0;
            SDL_Window* _window;
    };

}
