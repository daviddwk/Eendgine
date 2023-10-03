#pragma once

#include <SDL2/SDL.h>

namespace Eendgine {
    class FrameLimiter {
        public:
            static void setFPS(float fps);
            static void startInterval();
            static void stopInterval();
            inline static float deltaTime = 0; // sec 
        private:
            inline static int _startTicks = 0;
            inline static float _fps = 0;
    };
}
