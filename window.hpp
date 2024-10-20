#pragma once
#include <SDL2/SDL.h>
#include <string>
// #include <GLFW/glfw3.h>

namespace Eendgine {

class Window {
    public:
        static void init(int width, int height, std::string name);
        static void close();
        static void swapBuffers();
        static void processInput();
        /*
        inline static bool leftPress = false;
        inline static bool rightPress = false;
        inline static bool upPress = false;
        inline static bool downPress = false;
        inline static bool spacePress = false;
        inline static bool shouldClose = false;
        inline static int deltaMouseX = 0;
        inline static int deltaMouseY = 0;
        */
    private:
        static void framebuffer_size_callback(SDL_Window* window, int width, int height);
        static void key_callback(SDL_Window* window, int key, int scancode, int action, int mods);
        inline static int _width = 0;
        inline static int _height = 0;
        inline static SDL_Window* _window = nullptr;
        // inline static GLFWwindow* _window = nullptr;
        /*
        inline static int _posMouseX = 0;
        inline static int _posMouseY = 0;
        */
};
} // namespace Eendgine
