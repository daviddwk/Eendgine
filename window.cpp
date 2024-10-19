#include "window.hpp"
#include <iostream>

namespace Eendgine {
void framebuffer_size_callback(SDL_Window *window, int width, int height);
// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void Window::init(int width, int height, std::string name) {
    _width = width;
    _height = height;
    SDL_Init(SDL_INIT_EVERYTHING);
    /*
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    */
    /*
    GLFWwindow* window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    _window = window;
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    */
    _window = SDL_CreateWindow(
        name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);
    if (_window == nullptr) {
        std::cout << "Failed to create SDL window" << std::endl;
    }
    // glfwMakeContextCurrent(window);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        std::cout << "Failed to create SDL GL context" << std::endl;
    }

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    SDL_GL_SetSwapInterval(0);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    // glfwSetKeyCallback(window, key_callback);
}
/*
void Window::close() {
    glfwDestroyWindow(_window);
}
*/

void Window::swapBuffers() {
    SDL_GL_SwapWindow(_window);
    /*
    glfwSwapBuffers(_window);
    glfwPollEvents();
    */
}
/*
void Window::processInput() {
    //const unsigned char *keyState = SDL_GetKeyboardState(nullptr);

    glfwPollEvents();

    leftPress  = glfwGetKey(_window, GLFW_KEY_LEFT);
    rightPress = glfwGetKey(_window, GLFW_KEY_RIGHT);
    upPress    = glfwGetKey(_window, GLFW_KEY_UP);
    downPress  = glfwGetKey(_window, GLFW_KEY_DOWN);
    spacePress = glfwGetKey(_window, GLFW_KEY_SPACE);

    shouldClose = glfwGetKey(_window, GLFW_KEY_Q);

    double posMouseX, posMouseY;
    glfwGetCursorPos(_window, &posMouseX, &posMouseY);

    deltaMouseX = posMouseX - _posMouseX;
    deltaMouseY = posMouseY - _posMouseY;
    _posMouseX = posMouseX;
    _posMouseY = posMouseY;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
*/
/*
void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_Q) {
         shouldClose = true;
    }
}
*/
} // namespace Eendgine
