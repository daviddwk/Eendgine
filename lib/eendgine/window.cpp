#include "window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

namespace Eendgine {

    void Window::init(int width, int height, std::string name) {
        _width = width;
        _height = height;
        
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
        _window = window;
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }  
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void Window::swapBuffers() {
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
    
    void Window::processInput() {
        //const unsigned char *keyState = SDL_GetKeyboardState(nullptr);

        glfwPollEvents();
        
        leftPress  = glfwGetKey(_window, GLFW_KEY_LEFT);
        rightPress = glfwGetKey(_window, GLFW_KEY_RIGHT);
        upPress    = glfwGetKey(_window, GLFW_KEY_UP);
        downPress  = glfwGetKey(_window, GLFW_KEY_DOWN);
        spacePress = glfwGetKey(_window, GLFW_KEY_SPACE);

        double posMouseX, posMouseY;
        glfwGetCursorPos(_window, &posMouseX, &posMouseY);

        deltaMouseX = posMouseX - _posMouseX;
        deltaMouseY = posMouseY - _posMouseY;
        _posMouseX = posMouseX;
        _posMouseY = posMouseY;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
