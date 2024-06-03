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

void Ball::update(float dt) {
    // -55 55 z
    // -35 35 x
    // TODO don't have these be hardcoded obviously
    // have these initiazized with the ball and be member variables
    // probably
    // also generate floats actually
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xDistribution(-35, 35);
    std::uniform_int_distribution<> zDistribution(0, 55);
    _position = _sprite.getPosition();

    static bool reachedDestination = true;
    static bool courtSide = true;
    if (reachedDestination) {
        std::cout << "reached destination" << std::endl;
        courtSide = !courtSide;
        int xDestination = xDistribution(gen);
        int zDestination = zDistribution(gen);
        if (courtSide) {
            zDestination = -zDestination;
        }
        _destination = glm::vec3((float)xDestination, 0.0f, (float)zDestination);
        reachedDestination = false;
    } 
    std::cout << _destination.x << ' ' << _destination.y << ' ' << _destination.z << std::endl;

    glm::vec3 toDestination = _destination - _position;  
    toDestination = glm::vec3(toDestination.x, 0.0f, toDestination.z);

    glm::vec3 toDestinationNormal = glm::normalize(toDestination);
    std::cout << "destination length" << glm::length(toDestination) << std::endl;
    if (glm::length(toDestinationNormal) > glm::length(toDestination)) {
        std::cout << "short" << std::endl;
        reachedDestination = true;
    }
    _position = glm::vec3(
            _position.x + (toDestinationNormal.x * _speedMultiplier * dt),
            _position.y,
            _position.z + (toDestinationNormal.z * _speedMultiplier * dt));

    // make some more self referential function so this is not nessary
    _sprite.setPosition(_position);
    std::cout << _position.x << ' ' << _position.y << ' ' << _position.z << std::endl;
}
