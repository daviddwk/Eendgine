#include "court.hpp"

namespace Eend = Eendgine;

Court::Court(
        std::filesystem::path animationDir, std::filesystem::path collisionPath, 
        glm::vec3 position, glm::vec3 scale, float animSpeed, 
        std::vector<Eend::CollisionModel*>& collisionModels) :
    _animationId(Eend::Entities::AnimationBatch::insert("resources/court")),
    _collision("resources/courtCol/courtHitbox.obj"),
    _animSpeed(animSpeed)
{
    collisionModels.push_back(&_collision);
    auto& court = Eend::Entities::AnimationBatch::getRef(_animationId);
    court.setPosition(position);
    court.setScale(scale);
    _collision.setPosition(position);
    _collision.setScale(scale);
}

Court::~Court() {
    // rm collision model
    Eend::Entities::AnimationBatch::erase(_animationId);
}

void Court::update(float dt) {
    auto& court = Eend::Entities::AnimationBatch::getRef(_animationId);
    court.setAnim(court.getAnim() + (_animSpeed * dt));
}
