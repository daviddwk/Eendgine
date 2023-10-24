#include "collisionGeometry.hpp"
#include <cmath>

namespace Eendgine {
    bool colliding(CollisionSphere s1, CollisionSphere s2) {
        float dis = std::abs(glm::distance(s1.getPosition(), s2.getPosition()));
        return (dis < (s1.getRadius() + s2.getRadius())); 
    }
}
