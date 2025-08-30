#pragma once
#include <glm/glm.hpp>
#include <cmath>

namespace Eendgine {

using Scale = glm::vec3;
using Scale2D = glm::vec2;
using Point = glm::vec3;
using Point2D = glm::vec2;
using Vector = glm::vec3;
using Vector2D = glm::vec2;
using Rotation = glm::vec3;
using TransformationMatrix = glm::mat4;
using Color = glm::vec4;

class Triangle {
    public:
        Triangle(Point p1, Point p2, Point p3)
        : p1(p1), p2(p2), p3(p3) {};

        Point p1;
        Point p2;
        Point p3;
};

class Rectangle {
    public:
        Rectangle(Point2D upperLeft, Point2D lowerRight)
        : upperLeft(upperLeft), lowerRight(lowerRight) {};

        Point2D upperLeft;
        Point2D lowerRight;
};

class Sphere {
    public:
        Sphere(Point position, float radius)
        : position(position), radius(std::abs(radius)) {};

        Point position = Point(0.0f, 0.0f, 0.0f);
        float radius = 0;
};

} // namespace Eendgine
