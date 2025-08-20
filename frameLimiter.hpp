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

        inline static FrameLimiter* m_instance = nullptr;

        std::chrono::steady_clock::time_point m_startTime = std::chrono::steady_clock::now();
        float m_maxFps = 0;
        float m_minFps = 0;
};
} // namespace Eendgine
