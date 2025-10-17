#include <assert.h>
#include <print>

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_messagebox.h>
#include <SDL2/SDL_video.h>

#include "window.hpp"

namespace Eendgine {

Window::Window(int width, int height, std::string name) {
    m_width = width;
    m_height = height;
    SDL_Init(SDL_INIT_EVERYTHING);
    m_window = SDL_CreateWindow(
        name.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_width,
        m_height,
        SDL_WINDOW_OPENGL);
    if (m_window == nullptr) {
        std::print("Failed to create SDL window: {}\n", SDL_GetError());
    }
    SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
    if (glContext == nullptr) {
        std::print("Failed to create SDL GL context: {}", SDL_GetError());
    }
    SDL_GL_SetSwapInterval(0);
}

Window::~Window() { SDL_DestroyWindow(m_window); }

void Window::construct(int width, int height, std::string name) {
    assert(m_instance == nullptr);
    m_instance = new Window(width, height, name);
}

void Window::destruct() {
    assert(m_instance != nullptr);
    delete m_instance;
    m_instance = nullptr;
}

Window& Window::get() {
    assert(m_instance != nullptr);
    return *m_instance;
}
void framebuffer_size_callback(SDL_Window* window, int width, int height);
// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void Window::swapBuffers() { SDL_GL_SwapWindow(m_window); }
} // namespace Eendgine
