#pragma once
#include <glm/glm.hpp>
#include <cmath>
#include <string>
#include <vector>

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
                    _normal = glm::vec3(0.0f, 0.1f, 0.0f);
            };

            void setPosition(float x, float y, float z) { _position = glm::vec3(x, y, z); };
            void setNormal(float x, float y, float z) { _normal = glm::vec3(x, y, z); };

            glm::vec3 getPosition() { return _position; };
            glm::vec3 getNormal() { return _normal; };

        private:
            glm::vec3 _position;
            glm::vec3 _normal;
    };

    class CollisionTriangle {
        public:
            CollisionTriangle(){ for (int i = 0; i < 3; i++) verts[i] = glm::vec3(0.0f); };
            CollisionTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2){ 
                verts[0] = v0;
                verts[1] = v1;
                verts[2] = v2;
            };
            void setVerts(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2){ 
                verts[0] = v0;
                verts[1] = v1;
                verts[2] = v2;
            };
            glm::vec3 verts[3];
    };
    
    glm::vec3 closestTriPoint(glm::vec3 p, CollisionTriangle t);

    bool colliding(CollisionSphere s1, CollisionSphere s2, glm::vec3 *penetration);
    bool colliding(CollisionSphere s, CollisionPlane p, glm::vec3 *penetration);
    bool colliding(CollisionSphere s, CollisionTriangle t, glm::vec3 *penetration);

    void loadCollisionModel(std::string modelPath, std::vector<CollisionTriangle> collisionModel);
}
