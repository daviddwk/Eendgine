#include "ball.hpp"
#include "drawBatches.hpp"

#include <eendgine/random.hpp>

#include <random>
#include <numbers>
#include <cmath>

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

void Ball::setPosition(glm::vec3 position) {
    _position = position;
    _sprite.setPosition(position);
}

void Ball::update(float dt) {
    static bool reachedDestination = true;
    static bool courtSide = true;
    static float totalDistance = 0.0f;
    const glm::vec3 position = getPosition();
    
    if (reachedDestination) {
        courtSide = !courtSide;
        float xDestination = Eend::randomRange(-_halfCourtWidth, _halfCourtWidth);
        float zDestination = Eend::randomRange(0.0f, _halfCourtLength);
        if (courtSide) {
            zDestination = -zDestination;
        }
        _destination = glm::vec3(xDestination, 0.0f, zDestination);
        totalDistance = glm::length(_destination - position);
        reachedDestination = false;
    } 

    glm::vec3 toDestination = _destination - position;  
    toDestination = glm::vec3(toDestination.x, 0.0f, toDestination.z);
    glm::vec3 toDestinationNormal = glm::normalize(toDestination);

    if (glm::length(toDestinationNormal) > glm::length(toDestination)) {
        reachedDestination = true;
    }
    
    const float ratioTraveled = glm::length(toDestination) / totalDistance;
    const float height = std::sin(ratioTraveled * std::numbers::pi) * _peakHeight;
    setPosition (glm::vec3(
            position.x + (toDestinationNormal.x * _speedMultiplier * dt),
            height,
            position.z + (toDestinationNormal.z * _speedMultiplier * dt)));
}
