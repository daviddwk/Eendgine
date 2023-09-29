#pragma once

#include <SDL2/SDL.h>

namespace Eendgine {
    class FrameLimiter {
        public:
            void setFPS(float fps);
            void startInterval();
            void stopInterval();
            
        private:
            int _startTicks;
            float _frameTicks;

    };
}
