#include "random.hpp"
#include <random>
#include <cstdint>

namespace Eendgine {

float randomRange(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(gen);
}

int32_t randomRange(int32_t min, int32_t max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

int32_t randomIntLimit() {
    return randomRange(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max());
}

} // namespace Eendgine
