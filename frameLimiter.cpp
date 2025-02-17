#include "frameLimiter.hpp"
#include <SDL2/SDL.h>
#include <chrono>
#include <cmath>
#include <thread>

namespace Eendgine {

void FrameLimiter::init(float maxFps, float minFps) {
    _maxFps = maxFps;
    _minFps = minFps;
}

void FrameLimiter::close() {}

void FrameLimiter::startInterval() { _startTime = std::chrono::steady_clock::now(); }

float FrameLimiter::stopInterval() {
    const auto intervalTime = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::steady_clock::now() - _startTime)
                                  .count();
    const auto frameTime = std::chrono::microseconds((int)((1.0f / _maxFps) * 1000000.0f));
    if (intervalTime < frameTime.count()) {
        deltaTime =
            std::chrono::duration_cast<std::chrono::microseconds>(frameTime).count() / 1000000.0f;
    } else if (intervalTime < 1 / _minFps) {
        deltaTime = intervalTime;
    } else {
        deltaTime = 1 / _minFps;
    }
    return (float)intervalTime;
}
} // namespace Eendgine
