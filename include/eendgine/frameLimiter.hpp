#pragma once

#include <SDL2/SDL.h>

namespace Eendgine {
    


    class FrameLimiter {
        public:
            static void setFPS(float fps);
            static void startInterval();
            static void stopInterval();
            static float deltaTime; // sec 
        private:
            static int _startTicks;
            static float _fps;
    };
}
