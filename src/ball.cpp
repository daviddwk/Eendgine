#include "ball.hpp"

Ball::Ball(DrawBatches& drawBatches, std::vector<Eend::CollisionModel*>& collisionModels,
        Eend::TextureCache& textureCache, Eend::Camera3D& camera,
        glm::vec3 position, float radius) :
    _position(position),
    _sprite(textureCache.getTexture("resources/ball/diffuse.png"), camera), 
    _hitBox(position, radius),
    _collisionModels(collisionModels),
    _drawBatches(drawBatches)
{
    _drawBatches.insert(&_sprite);
}

Ball::~Ball() {
    _drawBatches.remove(&_sprite);
}
