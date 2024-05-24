#pragma once

#include <eendgine/sprite.hpp>
#include <eendgine/collisionGeometry.hpp>
#include <eendgine/camera.hpp>

#include "drawBatches.hpp"

namespace Eend = Eendgine;

class Ball {
    public:
        Ball(DrawBatches& drawBatches, std::vector<Eend::CollisionModel*>& collisionModels,
                Eend::TextureCache& textureCache, Eend::Camera3D& camera,
                glm::vec3 position, float radius);
        ~Ball();
        void update(float dt);
        void hit(bool hit);

    private:
        glm::vec3 _position;
        Eend::Sprite3D _sprite;
        Eend::CollisionSphere _hitBox;
        DrawBatches& _drawBatches;
        std::vector<Eend::CollisionModel*>& _collisionModels;
};
