#include "collisionGeometry.hpp"
#include "vertex.hpp"
#include "loadModel.hpp"
#include "fatalError.hpp"
#include <cmath>
#include <iostream>
#include <tuple>

float sign (glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
glm::vec3 triNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
float pointHeightOnTri(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float x, float z);
bool vertOnTri(glm::vec3 vert, std::array<glm::vec3, 3> tri);

namespace Eendgine {
    CollisionSphere::CollisionSphere(glm::vec3 position, float radius) :
            _position(position),
            _radius(std::abs(radius))
    {
    }
    CollisionPlane::CollisionPlane(glm::vec3 position, glm::vec3 normal) :
            _position(position),
            _normal(normal)
    { 
    }
    CollisionTriangle::CollisionTriangle(std::array<glm::vec3, 3> vertPositions,  std::array<glm::vec3, 3> vertNormals) :
            _verts(vertPositions)
    {
        // getting face normal from vertex normals by getting average (I think the math is fine)
        // https://math.stackexchange.com/questions/250165/converting-vertex-normals-to-face-normals
        _normal = glm::normalize(vertNormals[0] + vertNormals[1] + vertNormals[2]);
        // for collision
        if (_normal.y > 0.1f) {
            _surface = surface::floor;
        } else if (_normal.y < 0.1f) {
            _surface = surface::ceiling;
        } else {
            _surface = surface::wall;
        }
    }
    CollisionCylinder::CollisionCylinder(glm::vec3 position, float height, float radius) :
            _position(position),
            _height(height),
            _radius(radius)
    {
    }
    CollisionModel::CollisionModel(std::string modelPath) {
        std::vector <Vertex> vertices;
        std::vector <unsigned int> indices;
        loadModel(modelPath, vertices, indices);
        if (indices.size() % 3 != 0) {
            fatalError("collisionModel indices not divisible by 0");
        }
        for (int i = 0; i < indices.size(); i += 3){
            // TODO check for normals
            _collisionTris.emplace_back(
                    std::array<glm::vec3, 3>{
                        vertices[indices[i]].position,
                        vertices[indices[i + 1]].position,
                        vertices[indices[i + 2]].position
                    },
                    std::array<glm::vec3, 3>{
                        vertices[indices[i]].normal,
                        vertices[indices[i + 1]].normal,
                        vertices[indices[i + 2]].normal,
                    });
        }
    }
    
    bool colliding(CollisionSphere s1, CollisionSphere s2, glm::vec3 *penetration) {
        glm::vec3 distance = s2.getPosition() - s1.getPosition();
        float depth = (s1.getRadius() + s2.getRadius()) - glm::length(distance);
        std::cout << "depth"<< depth << std::endl;
        if (penetration != nullptr) {
            *penetration = depth * glm::normalize(distance);
        }
        return depth > 0.0f;
    }
    
    bool colliding(CollisionSphere s, CollisionPlane p, glm::vec3 *penetration) {
        float distance = glm::dot(p.getNormal(), (s.getPosition() - p.getPosition()));
        float depth = s.getRadius() - distance;
        if (penetration != nullptr) {
            glm::vec3 pen = (-p.getNormal()) * depth;
            *penetration = pen;
        }
        return depth > 0.0f;
    }

    

    bool snapCylinderToFloor(CollisionCylinder &c, CollisionModel &m, float *height) {
        float d1, d2, d3;
        bool has_neg, has_pos;
        
        glm::vec3 cylinderPos = c.getPosition();
        auto tris = m.getTris();
        for (auto& t : tris) {
            std::array<glm::vec3, 3> triVerts = t.getVerts();

            d1 = sign(cylinderPos, triVerts[0], triVerts[1]);
            d2 = sign(cylinderPos, triVerts[1], triVerts[2]);
            d3 = sign(cylinderPos, triVerts[2], triVerts[0]);

            has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
            has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

            float snapDistance = 0.2;
            if (!(has_neg && has_pos)) {
                *height = pointHeightOnTri(triVerts[0], triVerts[1], triVerts[2], cylinderPos.x, cylinderPos.z);
                // if slightly above floor OR clipping into floor
                if (fabs(cylinderPos.y - *height) <= snapDistance
                        || (cylinderPos.y - *height < 0 && cylinderPos.y - *height > -c.getHeight())){
                    *height += snapDistance;
                    return true;
                }
            }
        }
        return false;
    }
    
    bool pushCylinderFromWall(CollisionCylinder &c, CollisionModel &m, glm::vec3 *offset) {
        glm::vec3 cylinderPos = c.getPosition();
        auto tris = m.getTris();
        bool collision = false;
        *offset = glm::vec3(0);
        for (auto& t : tris) {
            glm::vec3 triNormal = t.getNormal();
            std::array<glm::vec3, 3> triVerts = t.getVerts();
            // vector from cylinder to any point on triangle
            glm::vec3 toTri = triVerts[0] - cylinderPos;
            // project vector onto plane of triangle with the tri's normal
            // https://math.stackexchange.com/questions/3481232/projection-of-vector-v-onto-a-plane-with-normal-vector-n
            glm::vec3 projection = toTri * triNormal;
            // if in triangular prisim (triangle with depth of radius)
            // move to the face which the normal vector points toward
            if (vertOnTri(projection + cylinderPos, t.getVerts()) && fabs(glm::length(projection)) < c.getRadius()) {
                *offset += (c.getRadius() - glm::length(projection)) * triNormal;
                collision = true;
            }
        }
        return collision;
    }
    /*
    bool colliding(CollisionSphere s, CollisionTriangle &t, glm::vec3 *penetration, glm::vec3 position, glm::vec3 scale) {
        glm::vec3 closestPoint = closestTriPoint(s.getPosition(), t, position, scale);
        glm::vec3 distance = closestPoint - s.getPosition();
        float depth = s.getRadius() - glm::length(distance);
        if (penetration != nullptr) {
            *penetration = depth * glm::normalize(distance);
        }
        return depth > 0.0f;
    }
    */

    /*
    bool colliding(CollisionSphere s, CollisionModel &m, std::vector<glm::vec3> *penetration) {
        bool collision = false;
        auto triangles = m.getTris();
        glm::vec3 modelPos = m.getPosition();
        glm::vec3 modelScale = m.getScale();
        glm::vec3 tmpPen = glm::vec3(0.0f);
        for ( int i = 0; i < triangles.size(); i++ ) {
            if (colliding(s, triangles[i], &tmpPen, modelScale, modelPos)) {
                penetration->push_back(tmpPen);
                collision = true;
            }
        } 
        return collision;
    }
    */
    /*
    glm::vec3 closestTriPoint(glm::vec3 p, CollisionTriangle t, glm::vec3 position, glm::vec3 scale) {
        // thanks to Real-Time Collision Detection by Christer Ericson
        auto verts = t.getVerts();
        glm::vec3 a = (verts[0] * scale) + position;
        glm::vec3 b = (verts[1] * scale) + position;
        glm::vec3 c = (verts[2] * scale) + position;
        glm::vec3 ab = verts[1] - verts[0];
        glm::vec3 ac = verts[2] - verts[0];
        glm::vec3 bc = verts[2] - verts[1];
        // Compute parametric position s for projection P’ of P on AB,
        // P’ = A + s*AB, s = snom/(snom+sdenom)
        float snom = glm::dot(p - a, ab), sdenom = glm::dot(p - b, a - b);
        // Compute parametric position t for projection P’ of P on AC,
        // P’ = A + t*AC, s = tnom/(tnom+tdenom)
        float tnom = glm::dot(p - a, ac), tdenom = glm::dot(p - c, a - c);
        if (snom <= 0.0f && tnom <= 0.0f) return a; // Vertex region early out
        // Compute parametric position u for projection P’ of P on BC,
        // P’ = B + u*BC, u = unom/(unom+udenom)
        float unom = glm::dot(p - b, bc), udenom = glm::dot(p - c, b - c);
        if (sdenom <= 0.0f && unom <= 0.0f) return b; // Vertex region early out
        if (tdenom <= 0.0f && udenom <= 0.0f) return c; // Vertex region early out
        // P is outside (or on) AB if the triple scalar product [N PA PB] <= 0
        glm::vec3 n = glm::cross(b - a, c - a);
        float vc = glm::dot(n, glm::cross(a - p, b - p));
        // If P outside AB and within feature region of AB,
        // return projection of P onto AB
        if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f) {
            return a + snom / (snom + sdenom) * ab;
        }
        // P is outside (or on) BC if the triple scalar product [N PB PC] <= 0
        float va = glm::dot(n, glm::cross(b - p, c - p));
        // If P outside BC and within feature region of BC,
        // return projection of P onto BC
        if (va <= 0.0f && unom >= 0.0f && udenom >= 0.0f) {
            return b + unom / (unom + udenom) * bc;
        }
        // P is outside (or on) CA if the triple scalar product [N PC PA] <= 0
        float vb = glm::dot(n, glm::cross(c - p, a - p));
        // If P outside CA and within feature region of CA,
        // return projection of P onto CA
        if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f) {
            return a + tnom / (tnom + tdenom) * ac;
        }
        // P must project inside face region. Compute Q using barycentric coordinates
        float u = va / (va + vb + vc);
        float v = vb / (va + vb + vc);
        float w = 1.0f - u - v; // = vc / (va + vb + vc)
        return u * a + v * b + w * c;
    }
    */
}

float sign (glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
    return ((p1.x - p3.x) * (p2.z - p3.z)) - ((p2.x - p3.x) * (p1.z - p3.z));
}
float pointHeightOnTri(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float x, float z){
    // undefined behavior if plane is parallel
    // WHAT? https://math.stackexchange.com/questions/1154340/how-to-find-the-height-of-a-2d-coordinate-on-a-3d-triangle
    float a = -(p3.z*p2.y-p1.z*p2.y-p3.z*p1.y+
            p1.y*p2.z+p3.y*p1.z-p2.z*p3.y);    
    float b = (p1.z*p3.x+p2.z*p1.x+p3.z*p2.x-
            p2.z*p3.x-p1.z*p2.x-p3.z*p1.x);    
    float c = (p2.y*p3.x+p1.y*p2.x+p3.y*p1.x-
            p1.y*p3.x-p2.y*p1.x-p2.x*p3.y);
    float d = -a*p1.x-b*p1.y-c*p1.z;
    return -(a*x+c*z+d)/b;  

}

glm::vec3 triNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
    // https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal
    glm::vec3 a = p2 - p1;
    glm::vec3 b = p3 - p1;

    return glm::vec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x);
}
bool vertOnTri(glm::vec3 vert, std::array<glm::vec3, 3> tri) {
    glm::vec3 u = tri[1] - tri[0];
    glm::vec3 v = tri[2] - tri[0];
    glm::vec3 w = vert - tri[0];
    float uu = glm::dot(u, u);
    float uv = glm::dot(u, v);
    float vv = glm::dot(v, v);
    float wu = glm::dot(w, u);
    float wv = glm::dot(w, v);
    float denominator = uv * uv - uu * vv;

    // Calculate barycentric coordinates
    float s = (uv * wv - vv * wu) / denominator;
    float t = (uv * wu - uu * wv) / denominator;
    return (s >= 0) && (t >= 0) && (s + t <= 1);
}
