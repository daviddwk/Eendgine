#include "collisionGeometry.hpp"
#include "vertex.hpp"
#include "loadModel.hpp"
#include "fatalError.hpp"
#include <cmath>
#include <iostream>
#include <tuple>

namespace Eendgine {
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

    bool colliding(CollisionSphere s, CollisionTriangle &t, glm::vec3 *penetration, glm::vec3 position, glm::vec3 scale) {
        glm::vec3 closestPoint = closestTriPoint(s.getPosition(), t, position, scale);
        glm::vec3 distance = closestPoint - s.getPosition();
        float depth = s.getRadius() - glm::length(distance);
        if (penetration != nullptr) {
            *penetration = depth * glm::normalize(distance);
        }
        return depth > 0.0f;
    }

    bool colliding(CollisionSphere s, CollisionModel &m, glm::vec3 *penetration) {
        bool collision = false;
        auto triangles = m.getTris();
        glm::vec3 modelPos = m.getPosition();
        glm::vec3 modelScale = m.getScale();
        glm::vec3 tmpPen = glm::vec3(0.0f);
        *penetration = tmpPen;
        for ( int i = 0; i < triangles.size(); i++ ) {
            if (colliding(s, triangles[i], &tmpPen, modelScale, modelPos)) {
                *penetration += tmpPen;
                collision = true;
            }
        } 
        return collision;
    }

    glm::vec3 closestTriPoint(glm::vec3 p, CollisionTriangle t, glm::vec3 position, glm::vec3 scale) {
        // thanks to Real-Time Collision Detection by Christer Ericson
        auto verts = t.getVerts();
        glm::vec3 a = (std::get<0>(verts) * scale) + position;
        glm::vec3 b = (std::get<1>(verts) * scale) + position;
        glm::vec3 c = (std::get<2>(verts) * scale) + position;
        glm::vec3 ab = b - a;
        glm::vec3 ac = c - a;
        glm::vec3 bc = c - b;
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

    CollisionModel::CollisionModel(std::string modelPath) {
        std::vector <Vertex> vertices;
        std::vector <unsigned int> indices;
        loadModel(modelPath, vertices, indices);
        if (indices.size() % 3 != 0) {
            fatalError("collisionModel indices not divisible by 0");
        }
        for (int i = 0; i < indices.size(); i += 3){
            _collisionTris.emplace_back(
                        vertices[indices[i]].position,
                        vertices[indices[i + 1]].position,
                        vertices[indices[i + 2]].position);
        }
    }
}
