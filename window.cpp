#include "window.hpp"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_messagebox.h>
#include <SDL2/SDL_video.h>
#include <iostream>

namespace Eendgine {
void framebuffer_size_callback(SDL_Window* window, int width, int height);
// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void Window::init(int width, int height, std::string name) {
    _width = width;
    _height = height;
    SDL_Init(SDL_INIT_EVERYTHING);
    _window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width,
        _height, SDL_WINDOW_OPENGL);
    if (_window == nullptr) {
        std::cout << "Failed to create SDL window" << std::endl;
        std::cout << SDL_GetError() << std::endl;
    }
    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        std::cout << "Failed to create SDL GL context" << std::endl;
        std::cout << SDL_GetError() << std::endl;
    }

    SDL_GL_SetSwapInterval(0);
}

void Window::close() { SDL_DestroyWindow(_window); }

void Window::swapBuffers() { SDL_GL_SwapWindow(_window); }
} // namespace Eendgine
