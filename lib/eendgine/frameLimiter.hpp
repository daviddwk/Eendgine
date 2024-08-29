#pragma once
#include <GLFW/glfw3.h>

namespace Eendgine {
    class FrameLimiter {
        public:
            static void setFPS(float fps);
            static void startInterval();
            static float stopInterval();
            inline static float deltaTime = 0; // sec 
        private:
            inline static float _startTime = 0;
            inline static float _fps = 0;
    };
}
