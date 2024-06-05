#include <random>
#include "eendgine/random.hpp"

namespace Eendgine {
    float randomRange(float min, float max) {
        std::uniform_real_distribution<float> distribution(min, max);
        return distribution(gen);
    }
}
