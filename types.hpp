#pragma once
#include <glm/glm.hpp>
#include <cmath>

namespace Eendgine {

constexpr float INV_SQRT_TWO = 0.7071f;

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

class Angle {
    public:
        Angle(float degrees) {
            setDegrees(degrees);
        };

        float getDegrees() { return m_degrees; };
        void setDegrees(float degrees) {
            float tmpDegrees = fmod(degrees, 360.0f);
            if (tmpDegrees < 0) {
                tmpDegrees = 360.0f - tmpDegrees;
            }
            m_degrees = tmpDegrees;
        };

        Angle operator+(const Angle& other) {
            return Angle(m_degrees + other.m_degrees);
        }
        Angle operator-(const Angle& other) {
            return Angle(m_degrees - other.m_degrees);
        }
        Angle operator*(const float factor) {
            return Angle(m_degrees * factor);
        }
        Angle operator/(const float divisor) {
            return Angle(m_degrees / divisor);
        }
        bool operator>(const Angle& other) {
            return m_degrees > other.m_degrees;
        }
        bool operator>=(const Angle& other) {
            return m_degrees >= other.m_degrees;
        }
        bool operator<(const Angle& other) {
            return m_degrees < other.m_degrees;
        }
        bool operator<=(const Angle& other) {
            return m_degrees <= other.m_degrees;
        }

    private:
        float m_degrees = 0;
};

} // namespace Eendgine
