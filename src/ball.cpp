#include "ball.hpp"
#include "drawBatches.hpp"

namespace Eend = Eendgine;

Ball::Ball(std::string texturePath, glm::vec3 position, 
        Eend::TextureCache& textureCache, Eend::Camera3D& camera, DrawBatches& drawBatches) :
    _position(position),
    _camera(camera),
    _sprite(textureCache.getTexture(texturePath), camera),
    _drawBatches(drawBatches)
{
    _drawBatches.insert(&_sprite);
    _sprite.setScale(10.0f, 10.0f);
}

Ball::~Ball() {
    _drawBatches.remove(&_sprite);
}

void Ball::update(float dt) {
}
