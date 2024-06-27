#include "ball.hpp"

#include <eendgine/random.hpp>
#include <eendgine/textureCache.hpp>

#include <random>
#include <numbers>
#include <cmath>

namespace Eend = Eendgine;

Ball::Ball(std::string texturePath, glm::vec3 position, float radius) :
    _position(position),
    _collision(position, radius)
{
    _billboardId = Eend::EntityBatches::insertBillboard({texturePath});
    auto _billboardRef = Eend::EntityBatches::getRefBillboard(_billboardId);
    _billboardRef->setPosition(glm::vec3(0.0f, 20.0f, 0.0f));
    _billboardRef->setScale(radius, radius);
}

Ball::~Ball() {
    Eend::EntityBatches::eraseBillboard(_billboardId);
}

void Ball::setPosition(glm::vec3 position) {
    auto _billboardRef = Eend::EntityBatches::getRefBillboard(_billboardId);
    _position = position;
    _billboardRef->setPosition(position);
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
