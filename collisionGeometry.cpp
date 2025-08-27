#include "collisionGeometry.hpp"
#include "types.hpp"

#include <cmath>
#include <omp.h>

namespace Eendgine {

CollisionSphere::CollisionSphere(Point position, float radius)
    : position(position), radius(std::abs(radius)) {}

bool pointOnRectangle(Point2D point, CollisionRectangle rectangle) {
    float behindLeft = point.x - rectangle.upperLeft.x; // negative means in front
    float behindTop = point.y - rectangle.upperLeft.y;
    float behindRight = rectangle.lowerRight.x - point.x;
    float behindBottom = rectangle.lowerRight.y - point.y;

    if (behindLeft > 0 && behindTop > 0 && behindRight > 0 && behindBottom > 0)
        return true;
    return false;
}

std::optional<Point> pointToSphereEdgeRelative(Point point, CollisionSphere sphere) {
    Point difference = point - sphere.position;
    float distance = glm::length(difference);
    if (distance < sphere.radius) {
        float depth = sphere.radius - distance;
        return std::optional<Point>(glm::normalize(difference) * (depth / sphere.radius));
    }
    return std::nullopt;    
}

float pointHeightOnTri(const Triangle& tri, const Point2D& point) {
    // could use a tri construct here instead of 3 points

    // calc tri normal
    // https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal
    const Point u = tri.p2 - tri.p1;
    const Point v = tri.p3 - tri.p1;
    const Point normal = glm::cross(u, v);
    // calc d for point normal plane
    const float d = -((normal.x * tri.p1.x) + (normal.y * tri.p1.y) + (normal.z * tri.p1.z));
    // solve for point.z
    return -((normal.x * point.x) + (normal.y * point.y) + d) / normal.z;
}

} // namespace Eendgine
