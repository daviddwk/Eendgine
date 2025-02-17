#pragma once

#include <chrono>

namespace Eendgine {
class FrameLimiter {
    public:
        static void init(float maxFps, float minFps);
        static void close();
        static void startInterval();
        static float stopInterval();
        inline static float deltaTime = 0; // sec
    private:
        inline static std::chrono::steady_clock::time_point _startTime =
            std::chrono::steady_clock::now();
        inline static float _maxFps = 0;
        inline static float _minFps = 0;
};
} // namespace Eendgine
