#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>
#include <cmath>
#include "frameLimiter.hpp"

namespace Eendgine {
    
    void FrameLimiter::init(float fps) {
        _fps = fps;
    }

    void FrameLimiter::close() {
    }

    void FrameLimiter::startInterval() {
        _startTime = glfwGetTime();
    }

    float FrameLimiter::stopInterval() {
        const float intervalTime = glfwGetTime() - _startTime;
        const float frameTime = 1.0f / _fps;
        if (intervalTime < frameTime){
            std::this_thread::sleep_for(
                    std::chrono::round<std::chrono::nanoseconds>(std::chrono::duration<float>{
                        frameTime - intervalTime
                    }));
            deltaTime = frameTime;
        } else {
            deltaTime = intervalTime;
        } 
        return (float)intervalTime;
    }
}
