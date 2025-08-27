#pragma once
#include <optional>

#include "types.hpp"

namespace Eendgine {


bool pointOnRectangle(Point2D point, Rectangle rectangle);
float pointHeightOnTri(const Triangle& tri, const Point2D& point);
std::optional<Point> pointToSphereEdgeRelative(Point point, Sphere sphere);

} // namespace Eendgine
