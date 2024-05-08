#pragma once
#include <glm/glm.hpp>
#include <cmath>
#include <string>
#include <vector>
#include <array>

namespace Eendgine {
    class CollisionSphere {
        public:
            CollisionSphere(glm::vec3 position, float radius);
            void setPosition(glm::vec3 position) { _position = position; };
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
            enum surface {floor, ceiling, wall};
            CollisionTriangle(std::array<glm::vec3, 3> vertPositions,  std::array<glm::vec3, 3> vertNormals);
            void setVerts(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) { _verts = {v0, v1, v2}; };
            std::array<glm::vec3, 3> getVerts() { return _verts; };
            glm::vec3 getNormal() { return _normal; }; 
            surface getSurface() { return _surface; }

        private:
            std::array<glm::vec3, 3> _verts;
            glm::vec3 _normal;
            surface _surface;
    };

    class CollisionCylinder {
        public:
            CollisionCylinder(glm::vec3 position, float height, float radius);

            void setPosition(glm::vec3 position) { _position = position; };
            void setHeight(float height) { _height = height; };
            void setRaduis(float radius) { _radius = radius; };

            glm::vec3 getPosition() { return _position; };
            float getHeight() { return _height; };
            float getRadius() { return _radius; };
        private:
            glm::vec3 _position;
            float _height;
            float _radius;
    };

    class CollisionModel {
        public:
            CollisionModel(std::string modelPath);
            void setPosition(glm::vec3 position) { _position = position; };
            void setScale(glm::vec3 scale) { _scale = scale; };
            glm::vec3 getPosition() { return _position; }; 
            glm::vec3 getScale() { return _scale; }; 
            std::vector<CollisionTriangle> getTris() {
                std::vector<CollisionTriangle> tris = _collisionTris;
                for (auto& t : tris) {
                    std::array<glm::vec3, 3> triVerts = t.getVerts();
                    for (auto& v : triVerts) {
                        v *= _scale;
                        v += _position;
                    }
                    t.setVerts(triVerts[0], triVerts[1], triVerts[2]);
                }
                return tris;
            };
        private:
            std::vector<CollisionTriangle> _collisionTris;
            glm::vec3 _position = glm::vec3(0.0f);
            glm::vec3 _scale = glm::vec3(1.0f);
    };
    

    bool colliding(CollisionSphere s1, CollisionSphere s2, glm::vec3 *penetration);
    bool colliding(CollisionSphere s, CollisionPlane p, glm::vec3 *penetration);
    
    bool snapCylinderToFloor(CollisionCylinder &c, CollisionTriangle &t, float &resHeight);
    bool pushCylinderFromCeiling(CollisionCylinder &c, CollisionTriangle &t, float &resHeight);
    bool pushCylinderFromWall(CollisionCylinder &c, CollisionTriangle &t, glm::vec3 &resPosition);
    glm::vec3 adjustToCollision(CollisionCylinder &c, std::vector<CollisionModel*> &models,
                                bool &hitWall, bool &hitCeiling, bool &hitFloor);
}
