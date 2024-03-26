#pragma once
#include <glm/glm.hpp>
#include <cmath>
#include <string>
#include <vector>
#include <array>

namespace Eendgine {
    class CollisionSphere {
        public:
            CollisionSphere(float x, float y, float z, float r);
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
            CollisionPlane(glm::vec3 position, glm::vec3 normal);

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
            CollisionTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
            void setVerts(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) { _verts = {v0, v1, v2}; };
            std::array<glm::vec3, 3> getVerts() { return _verts; };

        private:
            std::array<glm::vec3, 3> _verts;
    };

    class CollisionModel {
        public:
            CollisionModel(std::string modelPath);
            void setPosition(glm::vec3 position) { _position = position; };
            void setScale(glm::vec3 scale) { _scale = scale; };
            glm::vec3 getPosition() { return _position; }; 
            glm::vec3 getScale() { return _scale; }; 
            std::vector<CollisionTriangle>& getTris() { return _collisionTris; };
        private:
            std::vector<CollisionTriangle> _collisionTris;
            glm::vec3 _position = glm::vec3(0.0f);
            glm::vec3 _scale = glm::vec3(1.0f);
    };
    
    glm::vec3 closestTriPoint(glm::vec3 p, CollisionTriangle t, glm::vec3 position, glm::vec3 scale);

    bool colliding(CollisionSphere s1, CollisionSphere s2, glm::vec3 *penetration);
    bool colliding(CollisionSphere s, CollisionPlane p, glm::vec3 *penetration);
    bool colliding(CollisionSphere s, CollisionTriangle &t, glm::vec3 *penetration, 
            glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
    bool colliding(CollisionSphere s, CollisionModel &m, std::vector<glm::vec3>* penetrations);
    
    bool snapToTri(CollisionSphere s, CollisionModel &m, float *height);

    void loadCollisionModel(std::string modelPath, std::vector<CollisionTriangle> &collisionModel);
}
