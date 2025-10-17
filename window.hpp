#pragma once

#include <filesystem>
#include <string>

#include <SDL2/SDL.h>

namespace Eendgine {

class Window {
    public:
        static void construct(int width, int height, std::string name);
        static void destruct();
        static Window& get();

        void swapBuffers();
        void processInput();

    private:
        Window(int width, int height, std::string name);
        ~Window();

        inline static Window* m_instance = nullptr;

        void framebuffer_size_callback(SDL_Window* window, int width, int height);
        void key_callback(SDL_Window* window, int key, int scancode, int action, int mods);

        int m_width = 0;
        int m_height = 0;
        SDL_Window* m_window = nullptr;
};
} // namespace Eendgine
