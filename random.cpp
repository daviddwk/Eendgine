#include "random.hpp"
#include <random>

namespace Eendgine {

float randomRange(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(gen);
}

int randomRange(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

int randomIntLimit() {
    return randomRange(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

} // namespace Eendgine
