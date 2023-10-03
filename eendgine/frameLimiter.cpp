#include <eendgine/frameLimiter.hpp>

namespace Eendgine {
    
    void FrameLimiter::setFPS(float fps) {
        _fps = fps;
    }

    void FrameLimiter::startInterval() {
        _startTicks = SDL_GetTicks();
    }

    void FrameLimiter::stopInterval() {
        float intervalTicks = (float)(SDL_GetTicks() - _startTicks);
        float frameTicks = 1000.0f / _fps;
        if (intervalTicks < frameTicks){
            SDL_Delay((Uint32)(frameTicks - intervalTicks));
            deltaTime = frameTicks / 1000.0f;
        } else {
            deltaTime = intervalTicks / 1000.0f;
        } 
    }
}
