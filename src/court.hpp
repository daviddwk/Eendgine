#pragma once

#include <eendgine/collisionGeometry.hpp>
#include <eendgine/entityBatches.hpp>

#include <filesystem>

namespace Eend = Eendgine;

class Court {
    public:
        Court(std::filesystem::path animationDir, std::filesystem::path collisionPath,
                glm::vec3 position, glm::vec3 scale, float animSpeed,
                std::vector<Eend::CollisionModel*>& collisionModels);
        ~Court();
        
        void update(float dt);
    private:
        Eend::AnimationId _animationId;
        Eend::CollisionModel _collision;
        float _animSpeed = 0.0f;
};
