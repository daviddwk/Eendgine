#include "ball.hpp"
#include "drawBatches.hpp"

#include <eendgine/random.hpp>

#include <random>
#include <numbers>
#include <cmath>

namespace Eend = Eendgine;

Ball::Ball(std::string texturePath, glm::vec3 position, float radius, 
        Eend::TextureCache& textureCache, Eend::Camera3D& camera, DrawBatches& drawBatches) :
    _position(position),
    _camera(camera),
    _sprite(textureCache.getTexture(texturePath), camera),
    _drawBatches(drawBatches),
    _collision(position, radius)
{
    _sprite.setPosition(glm::vec3(0.0f, 20.0f, 0.0f));
    _sprite.setScale(radius, radius);
    _drawBatches.insert(&_sprite);
}

Ball::~Ball() {
    _drawBatches.remove(&_sprite);
}

void Ball::setPosition(glm::vec3 position) {
    _position = position;
    _sprite.setPosition(position);
    _collision.setPosition(position);
}

void Ball::hit() {
    _hit = true;
}

void Ball::update(float dt) {
    const glm::vec3 position = getPosition();
    
    if (_hit) {
        _courtSide = !_courtSide;
        float xDestination = Eend::randomRange(-_halfCourtWidth, _halfCourtWidth);
        float zDestination = Eend::randomRange(0.0f, _halfCourtLength);
        if (_courtSide) {
            zDestination = -zDestination;
        }
        _destination = glm::vec3(xDestination, 0.0f, zDestination);
        _totalDistance = glm::length(_destination - position);
        _reachedDestination = false;
        _hit = false;
    } 

    glm::vec3 toDestination = _destination - position;  
    toDestination = glm::vec3(toDestination.x, 0.0f, toDestination.z);
    glm::vec3 toDestinationNormal = glm::normalize(toDestination);

    if (glm::length(toDestinationNormal) > glm::length(toDestination)) {
        _reachedDestination = true;
    }
    
    const float ratioTraveled = glm::length(toDestination) / _totalDistance;
    const float height = std::sin(ratioTraveled * std::numbers::pi) * _peakHeight;
    
    if (!_reachedDestination) {
        setPosition(glm::vec3(
                position.x + (toDestinationNormal.x * _speedMultiplier * dt),
                height,
                position.z + (toDestinationNormal.z * _speedMultiplier * dt)));
    }
}
