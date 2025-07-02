#include <assert.h>
#include <print>

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_messagebox.h>
#include <SDL2/SDL_video.h>

#include "window.hpp"

namespace Eendgine {

Window::Window(int width, int height, std::string name) {
    _width = width;
    _height = height;
    SDL_Init(SDL_INIT_EVERYTHING);
    _window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width,
        _height, SDL_WINDOW_OPENGL);
    if (_window == nullptr) {
        std::print("Failed to create SDL window: {}\n", SDL_GetError());
    }
    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        std::print("Failed to create SDL GL context: {}", SDL_GetError());
    }
    SDL_GL_SetSwapInterval(0);
}

Window::~Window() { SDL_DestroyWindow(_window); }

void Window::construct(int width, int height, std::string name) {
    assert(_instance == nullptr);
    _instance = new Window(width, height, name);
}

void Window::destruct() {
    assert(_instance != nullptr);
    delete _instance;
    _instance = nullptr;
}

Window& Window::get() {
    assert(_instance != nullptr);
    return *_instance;
}
void framebuffer_size_callback(SDL_Window* window, int width, int height);
// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void Window::swapBuffers() { SDL_GL_SwapWindow(_window); }
} // namespace Eendgine
