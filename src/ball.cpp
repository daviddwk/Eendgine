#include "ball.hpp"
#include "drawBatches.hpp"

#include <random>

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
    // -55 55 z
    // -35 35 x
    // TODO don't have these be hardcoded obviously
    // have these initiazized with the ball and be member variables
    // probably
    std::random_device rng;
    std::mt19937 gen(rng());
    std::uniform_real_distribution<float> xDistribution(-35.0f, 35.0f);
    std::uniform_real_distribution<float> zDistribution( 0.0f,  50.0f);
    glm::vec3 position = getPosition();

    static bool reachedDestination = true;
    static bool courtSide = true;
    if (reachedDestination) {
        courtSide = !courtSide;
        float xDestination = xDistribution(gen);
        float zDestination = zDistribution(gen);
        if (courtSide) {
            zDestination = -zDestination;
        }
        _destination = glm::vec3(xDestination, 0.0f, zDestination);
        reachedDestination = false;
    } 

    glm::vec3 toDestination = _destination - position;  
    toDestination = glm::vec3(toDestination.x, 0.0f, toDestination.z);

    glm::vec3 toDestinationNormal = glm::normalize(toDestination);
    if (glm::length(toDestinationNormal) > glm::length(toDestination)) {
        reachedDestination = true;
    }
    position = glm::vec3(
            position.x + (toDestinationNormal.x * _speedMultiplier * dt),
            position.y,
            position.z + (toDestinationNormal.z * _speedMultiplier * dt));

    setPosition(position);
}
