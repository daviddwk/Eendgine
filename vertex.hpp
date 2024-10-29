#pragma once
#include "types.hpp"
#include <glm/glm.hpp>

namespace Eendgine {
struct Vertex {
        Point position = Point(0.0f);
        Color color = Color(0.0f);
        Point2D uv = Point2D(0.0f);
        Point normal = Point(0.0f);
};

struct InpolVertex {
        Point position = Point(0.0f);
        Point nextPosition = Point(0.0f);
        Color color = Color(0.0f);
        Point2D uv = Point2D(0.0f);
        Point normal = Point(0.0f);
        Point nextNormal = Point(0.0f);
};
} // namespace Eendgine
