#include "frameLimiter.hpp"
#include <SDL2/SDL.h>
#include <chrono>
#include <cmath>
#include <thread>

namespace Eendgine {

void FrameLimiter::init(float fps) { _fps = fps; }

void FrameLimiter::close() {}

void FrameLimiter::startInterval() { _startTime = SDL_GetTicks(); }

float FrameLimiter::stopInterval() {
    const float intervalTime = SDL_GetTicks() - _startTime;
    const float frameTime = 1.0f / _fps;
    if (intervalTime < frameTime) {
        std::this_thread::sleep_for(std::chrono::round<std::chrono::nanoseconds>(
            std::chrono::duration<float>{frameTime - intervalTime}));
        deltaTime = frameTime;
    } else {
        deltaTime = intervalTime;
    }
    return (float)intervalTime;
}
} // namespace Eendgine
