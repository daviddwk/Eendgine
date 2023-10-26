#include "collisionGeometry.hpp"
#include <cmath>
#include <iostream>

namespace Eendgine {
    bool colliding(CollisionSphere s1, CollisionSphere s2, glm::vec3 *penetration) {
        glm::vec3 distance = s2.getPosition() - s1.getPosition();
        float depth = (s1.getRadius() + s2.getRadius()) - glm::length(distance);
        std::cout << "depth"<< depth << std::endl;
        if (penetration != nullptr) {
            *penetration = depth * glm::normalize(distance);
        }
        return depth > 0.0f;
    }
    
    bool colliding(CollisionSphere s, CollisionPlane p, glm::vec3 *penetration) {
        float distance = glm::dot(p.getNormal(), (s.getPosition() - p.getPosition()));
        float depth = s.getRadius() - distance;
        if (penetration != nullptr) {
            glm::vec3 pen = (-p.getNormal()) * depth;
            *penetration = pen;
        }
        return depth > 0.0f;
    }

    bool colliding(CollisionSphere s, CollisionTriangle t, glm::vec3 *penetration) {
        // sphere at origin
        glm::vec3 v0 = t.verts[0] - s.getPosition();
        glm::vec3 v1 = t.verts[1] - s.getPosition();
        glm::vec3 v2 = t.verts[2] - s.getPosition();
        // get triangle normal
        glm::vec3 normToTri = glm::cross(v1 - v0, v2 - v0);
        glm::vec3 normal = glm::normalize(normToTri);
        // distance from plane 
        float planeDis = glm::dot(normal, (s.getPosition() - v0));
        float depth = s.getRadius() - planeDis; 
        if (penetration != nullptr) {
            glm::vec3 pen = (-normal) * depth;
            *penetration = pen;
        }   
        return depth > 0.0f;
    }
}
