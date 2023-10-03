#include <eendgine/frameLimiter.hpp>

#include <iostream>

namespace Eendgine {
    
    float FrameLimiter::deltaTime = 0;
    int FrameLimiter::_startTicks = 0;
    float FrameLimiter::_fps = 0;
    
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
        std::cout << "dt:" << deltaTime << std::endl;
    }
}
