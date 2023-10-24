#pragma once
#include <glm/glm.hpp>
#include <cmath>

namespace Eendgine {
    class CollisionSphere {
        public:
            CollisionSphere(float x, float y, float z, float r) { 
                    _position = glm::vec3(x, y, z);
                    _radius = std::abs(r); };

            void setPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); };
            void setRadius(float r) { _radius = std::abs(r); };

            glm::vec3 getPosition() { return _position; };
            float getRadius() { return _radius; };
            
        private:
            glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);
            // radius loops to be safe
            float _radius = 0;
    };

    bool colliding(CollisionSphere s1, CollisionSphere s2);
}
