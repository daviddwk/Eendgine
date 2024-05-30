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
    _sprite.setPosition(glm::vec3(0.0f, 20.0f, 0.0f));
    _sprite.setScale(10.0f, 10.0f);
    _drawBatches.insert(&_sprite);
}

Ball::~Ball() {
    _drawBatches.remove(&_sprite);
}

void Ball::update(float dt) {
    // -55 55 z
    // -35 35 x
    glm::vec3 currentPosition = _sprite.getPosition();
    _sprite.setPosition(glm::vec3(
                currentPosition.x, 
                currentPosition.y + (dt * 10), 
                currentPosition.z + (dt * 10)));
}
