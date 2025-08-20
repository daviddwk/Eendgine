#pragma once
#include <array>
#include <cmath>
#include <filesystem>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

#include "types.hpp"

namespace Eendgine {
struct CollisionResults {
        std::optional<float> floor;
        std::optional<Point> wall;
        std::optional<float> ceiling;
};

struct CollisionRectangle {
        Point2D upperLeft;
        Point2D lowerRight;
};

class CollisionSphere {
    public:
        CollisionSphere(Point position, float radius);
        void setPosition(Point position) { m_position = position; };
        void setRadius(float r) { m_radius = std::abs(r); };

        Point getPosition() { return m_position; };
        float getRadius() { return m_radius; };

    private:
        Point m_position = Point(0.0f, 0.0f, 0.0f);
        // radius loops to be safe
        float m_radius = 0;
};

class CollisionPlane {
    public:
        CollisionPlane(Point position, Point normal);

        void setPosition(float x, float y, float z) { m_position = Point(x, y, z); };
        void setNormal(float x, float y, float z) { m_normal = Point(x, y, z); };

        Point getPosition() { return m_position; };
        Point getNormal() { return m_normal; };

    private:
        Point m_position;
        Point m_normal;
};

class CollisionTriangle {
    public:
        enum surface { FLOOR, CEILING, WALL };
        CollisionTriangle(std::array<Point, 3> vertPositions, std::array<Point, 3> vertNormals);
        void setVerts(Point v0, Point v1, Point v2) { m_verts = {v0, v1, v2}; };
        std::array<Point, 3> getVerts() { return m_verts; };
        Point getNormal() { return m_normal; };
        surface getSurface() { return m_surface; }

    private:
        std::array<Point, 3> m_verts;
        Point m_normal;
        surface m_surface;
};

class CollisionCylinder {
    public:
        CollisionCylinder(Point position, float height, float radius);

        void setPosition(Point position) { m_position = position; };
        void setHeight(float height) { m_height = height; };
        void setRaduis(float radius) { m_radius = radius; };

        Point getPosition() { return m_position; };
        float getHeight() { return m_height; };
        float getRadius() { return m_radius; };

    private:
        Point m_position;
        float m_height;
        float m_radius;
};

class CollisionModel {
    public:
        CollisionModel(std::filesystem::path modelPath);
        void setPosition(Point position) { m_position = position; };
        void setScale(Point scale) { m_scale = scale; };
        Point getPosition() { return m_position; };
        Point getScale() { return m_scale; };
        std::vector<CollisionTriangle> getTris() {
            std::vector<CollisionTriangle> tris = m_collisionTris;
            for (auto& t : tris) {
                std::array<Point, 3> triVerts = t.getVerts();
                for (auto& v : triVerts) {
                    v *= m_scale;
                    v += m_position;
                }
                t.setVerts(triVerts[0], triVerts[1], triVerts[2]);
            }
            return tris;
        };

    private:
        std::vector<CollisionTriangle> m_collisionTris;
        Point m_position = Point(0.0f);
        Point m_scale = Point(1.0f);
};

bool colliding(CollisionSphere s1, CollisionSphere s2, Point* penetration);
bool colliding(CollisionSphere s, CollisionPlane p, Point* penetration);
bool colliding(Point2D point, CollisionRectangle rectangle);

float snapCylinderToFloor(CollisionCylinder& c, CollisionTriangle& t);
Point pushCylinderFromWall(CollisionCylinder& c, CollisionTriangle& t);
std::optional<float> pushCylinderFromCeiling(CollisionCylinder& c, CollisionTriangle& t);
CollisionResults adjustToCollision(CollisionCylinder& c, std::vector<CollisionModel*>& models);
} // namespace Eendgine
