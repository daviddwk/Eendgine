#pragma once

namespace Eendgine {
class FrameLimiter {
  public:
    static void init(float fps);
    static void close();
    static void startInterval();
    static float stopInterval();
    inline static float deltaTime = 0; // sec
  private:
    inline static float _startTime = 0;
    inline static float _fps = 0;
};
} // namespace Eendgine
