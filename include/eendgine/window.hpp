#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Eendgine {

    class Window {
        public:
            Window();
            ~Window();

            void init(int width, int height, std::string name);
            bool shouldClose();
            void swapBuffers();

            void pollEvents();
            void processInput();

        private:
            int _width;
            int _height;
            GLFWwindow* _window;
    };

}
