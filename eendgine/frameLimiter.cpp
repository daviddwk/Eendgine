#include <eendgine/frameLimiter.hpp>

#include <iostream>

namespace Eendgine {
    
    void FrameLimiter::setFPS(float fps) {
        _frameTicks = 1000.0f / fps;
    }

    void FrameLimiter::startInterval() {
        _startTicks = SDL_GetTicks();
    }

    void FrameLimiter::stopInterval() {
        int intervalTicks = SDL_GetTicks() - _startTicks;
        if (intervalTicks < _frameTicks){
            SDL_Delay((Uint32)(_frameTicks - intervalTicks));
        }
    }
}
