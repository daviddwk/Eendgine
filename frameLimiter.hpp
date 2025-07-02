#pragma once

#include <chrono>

namespace Eendgine {
class FrameLimiter {
    public:
        static void construct(float maxFps, float minFps);
        static void destruct();
        static FrameLimiter& get();

        void startInterval();
        float stopInterval();
        float deltaTime = 0; // sec
    private:
        FrameLimiter(float maxFps, float minFps);
        ~FrameLimiter();

        inline static FrameLimiter* _instance = nullptr;

        std::chrono::steady_clock::time_point _startTime = std::chrono::steady_clock::now();
        float _maxFps = 0;
        float _minFps = 0;
};
} // namespace Eendgine
