#include <random>

namespace Eendgine {
    static std::random_device rng;
    static std::minstd_rand gen(rng());

    float randomRange(float min, float max);
}
