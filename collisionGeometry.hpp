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
        void setPosition(Point position) { _position = position; };
        void setRadius(float r) { _radius = std::abs(r); };

        Point getPosition() { return _position; };
        float getRadius() { return _radius; };

    private:
        Point _position = Point(0.0f, 0.0f, 0.0f);
        // radius loops to be safe
        float _radius = 0;
};

class CollisionPlane {
    public:
        CollisionPlane(Point position, Point normal);

        void setPosition(float x, float y, float z) { _position = Point(x, y, z); };
        void setNormal(float x, float y, float z) { _normal = Point(x, y, z); };

        Point getPosition() { return _position; };
        Point getNormal() { return _normal; };

    private:
        Point _position;
        Point _normal;
};

class CollisionTriangle {
    public:
        enum surface { FLOOR, CEILING, WALL };
        CollisionTriangle(std::array<Point, 3> vertPositions, std::array<Point, 3> vertNormals);
        void setVerts(Point v0, Point v1, Point v2) { _verts = {v0, v1, v2}; };
        std::array<Point, 3> getVerts() { return _verts; };
        Point getNormal() { return _normal; };
        surface getSurface() { return _surface; }

    private:
        std::array<Point, 3> _verts;
        Point _normal;
        surface _surface;
};

class CollisionCylinder {
    public:
        CollisionCylinder(Point position, float height, float radius);

        void setPosition(Point position) { _position = position; };
        void setHeight(float height) { _height = height; };
        void setRaduis(float radius) { _radius = radius; };

        Point getPosition() { return _position; };
        float getHeight() { return _height; };
        float getRadius() { return _radius; };

    private:
        Point _position;
        float _height;
        float _radius;
};

class CollisionModel {
    public:
        CollisionModel(std::filesystem::path modelPath);
        void setPosition(Point position) { _position = position; };
        void setScale(Point scale) { _scale = scale; };
        Point getPosition() { return _position; };
        Point getScale() { return _scale; };
        std::vector<CollisionTriangle> getTris() {
            std::vector<CollisionTriangle> tris = _collisionTris;
            for (auto& t : tris) {
                std::array<Point, 3> triVerts = t.getVerts();
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
        Point _position = Point(0.0f);
        Point _scale = Point(1.0f);
};

bool colliding(CollisionSphere s1, CollisionSphere s2, Point* penetration);
bool colliding(CollisionSphere s, CollisionPlane p, Point* penetration);
bool colliding(Point2D point, CollisionRectangle rectangle);

float snapCylinderToFloor(CollisionCylinder& c, CollisionTriangle& t);
Point pushCylinderFromWall(CollisionCylinder& c, CollisionTriangle& t);
std::optional<float> pushCylinderFromCeiling(CollisionCylinder& c, CollisionTriangle& t);
CollisionResults adjustToCollision(CollisionCylinder& c, std::vector<CollisionModel*>& models);
} // namespace Eendgine
