#include <eendgine/window.hpp>

#include <glad/glad.h>

#include <iostream>

namespace Eendgine {

    Window::Window() {

    }

    Window::~Window() {

    }

    void Window::init(int width, int height, std::string name) {
        _width = width;
        _height = height;

        
        _window = SDL_CreateWindow(name.c_str(), 
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);
        if (_window == nullptr) {
            std::cout << "Failed to create SDL window" << std::endl; 
        }

        SDL_GLContext glContext = SDL_GL_CreateContext(_window);
        if (glContext == nullptr) {
            std::cout << "Failed to create SDL GL context" << std::endl; 
        }
        
        SDL_GL_MakeCurrent(_window, glContext);

        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }    

        glViewport(0, 0, _width, _height);

    }

    void Window::pollEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                shouldClose = true;
            }
        }
    }

    void Window::swapBuffers() {
        SDL_GL_SwapWindow(_window);
    }

}
