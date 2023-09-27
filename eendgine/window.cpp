#include <iostream>
#include <eendgine/window.hpp>

namespace Eendgine {

    Window::Window() {

    }

    Window::~Window() {

    }

    void Window::init(int width, int height, std::string name) {
        _width = width;
        _height = height;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


        _window = glfwCreateWindow(_width, _height, name.c_str(), NULL, NULL);
        if (_window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl; 
        }

        glfwMakeContextCurrent(_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }   
        glViewport(0, 0, _width, _height);

    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(_window);
    }

    void Window::swapBuffers() {
        glfwSwapBuffers(_window);
    }

    void Window::pollEvents() {
        glfwPollEvents();
    }

    void Window::processInput() {
        if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(_window, true);
        }
    }
}
