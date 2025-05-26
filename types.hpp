#pragma once
#include <glm/glm.hpp>

namespace Eendgine {

using Scale = glm::vec3;
using Scale2D = glm::vec2;
using Point = glm::vec3;
using Point2D = glm::vec2;
// should this be a vec3 for 3D???
using Rotation = glm::vec3;
using TransformationMatrix = glm::mat4;
using Color = glm::vec4;

struct Triangle {
        Point p1;
        Point p2;
        Point p3;
};

} // namespace Eendgine
