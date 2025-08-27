#pragma once
#include <optional>

#include "types.hpp"

namespace Eendgine {

struct CollisionRectangle {
        Point2D upperLeft;
        Point2D lowerRight;
};

class CollisionSphere {
    public:
        CollisionSphere(Point position, float radius);

        Point position = Point(0.0f, 0.0f, 0.0f);
        // radius loops to be safe
        float radius = 0;
};

bool pointOnRectangle(Point2D point, CollisionRectangle rectangle);
float pointHeightOnTri(const Triangle& tri, const Point2D& point);
std::optional<Point> pointToSphereEdgeRelative(Point point, CollisionSphere sphere);

} // namespace Eendgine
