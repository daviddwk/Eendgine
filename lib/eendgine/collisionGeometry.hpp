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

    class CollisionPlane {
        public:
            CollisionPlane(){ 
                    _position = glm::vec3(0.0f);
                    _size = glm::vec2(0.0f);
                    _normal = glm::vec3(0.0f);
            };

            void setPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); };
            void setSize(float w, float h) { _size = glm::vec2(w, h); };
            void setNormal(float x, float y, float z) { _normal = glm::vec3(x, y, z); };

            glm::vec3 getPosition() { return _position; };
            glm::vec2 getSize() { return _size; };
            glm::vec3 getNormal() { return _normal; };

        private:
            glm::vec3 _position;
            glm::vec2 _size;
            glm::vec3 _normal;
    };

    bool colliding(CollisionSphere s1, CollisionSphere s2, glm::vec3 *penetration);
    bool colliding(CollisionSphere s1, CollisionSphere s2);
    bool colliding(CollisionSphere s, CollisionPlane p, glm::vec3 *penetration);
    bool colliding(CollisionSphere s, CollisionPlane p);
}
