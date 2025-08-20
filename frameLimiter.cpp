#include "frameLimiter.hpp"

#include <SDL2/SDL.h>

#include <assert.h>
#include <chrono>
#include <thread>

namespace Eendgine {

FrameLimiter::FrameLimiter(float maxFps, float minFps) : m_maxFps(maxFps), m_minFps(minFps) {}

FrameLimiter::~FrameLimiter() {}

void FrameLimiter::construct(float maxFps, float minFps) {
    assert(m_instance == nullptr);
    m_instance = new FrameLimiter(maxFps, minFps);
}

void FrameLimiter::destruct() {
    assert(m_instance != nullptr);
    delete m_instance;
    m_instance = nullptr;
}

FrameLimiter& FrameLimiter::get() {
    assert(m_instance != nullptr);
    return *m_instance;
}

void FrameLimiter::startInterval() { m_startTime = std::chrono::steady_clock::now(); }

float FrameLimiter::stopInterval() {

    std::chrono::milliseconds intervalTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - m_startTime);
    const auto minLength = std::chrono::milliseconds((int)((1.0f / m_maxFps) * 1000.0f));
    const auto maxLength = std::chrono::milliseconds((int)((1.0f / m_minFps) * 1000.0f));

    if (intervalTime.count() < minLength.count()) {
        deltaTime = minLength.count() / 1000.0f;
        std::this_thread::sleep_until(m_startTime + minLength);
    } else if (intervalTime.count() < maxLength.count()) {
        deltaTime = intervalTime.count() / 1000.0f;
    } else {
        deltaTime = maxLength.count() / 1000.0f;
    }
    return (float)intervalTime.count() / 1000.0f;
}
} // namespace Eendgine
