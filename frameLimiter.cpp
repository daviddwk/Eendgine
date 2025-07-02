#include "frameLimiter.hpp"

#include <SDL2/SDL.h>

#include <assert.h>
#include <chrono>
#include <thread>

namespace Eendgine {

FrameLimiter::FrameLimiter(float maxFps, float minFps) : _maxFps(maxFps), _minFps(minFps) {}

FrameLimiter::~FrameLimiter() {}

void FrameLimiter::construct(float maxFps, float minFps) {
    assert(_instance == nullptr);
    _instance = new FrameLimiter(maxFps, minFps);
}

void FrameLimiter::destruct() {
    assert(_instance != nullptr);
    delete _instance;
    _instance = nullptr;
}

FrameLimiter& FrameLimiter::get() {
    assert(_instance != nullptr);
    return *_instance;
}

void FrameLimiter::startInterval() { _startTime = std::chrono::steady_clock::now(); }

float FrameLimiter::stopInterval() {

    std::chrono::milliseconds intervalTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - _startTime);
    const auto minLength = std::chrono::milliseconds((int)((1.0f / _maxFps) * 1000.0f));
    const auto maxLength = std::chrono::milliseconds((int)((1.0f / _minFps) * 1000.0f));

    if (intervalTime.count() < minLength.count()) {
        deltaTime = minLength.count() / 1000.0f;
        std::this_thread::sleep_until(_startTime + minLength);
    } else if (intervalTime.count() < maxLength.count()) {
        deltaTime = intervalTime.count() / 1000.0f;
    } else {
        deltaTime = maxLength.count() / 1000.0f;
    }
    return (float)intervalTime.count() / 1000.0f;
}
} // namespace Eendgine
