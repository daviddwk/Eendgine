#include "player.hpp"
#include <eendgine/inputManager.hpp>
// DEBUG
#include <chrono>
namespace Eend = Eendgine;

Player::Player(std::vector<Eend::CollisionModel*>& collisionModels,
        glm::vec3 position, 
        std::string modelPath, Eend::Camera3D& camera, 
        float hitHeight, float hitRadius, float modelOffset, 
        float strikeRadius, float strikeOffset) :
    _hitBox(position, hitHeight, hitRadius),
    _strikeCollision(position + glm::vec3(0.0f, strikeOffset, 0.0f), strikeRadius),
    _position(position),
    _strikeOffset(strikeOffset),
    _modelOffset(modelOffset),
    _camera(camera),
    _cameraRotation(0.0f, 0.0f),
    _fallVelocity(0.0f),
    _cameraDistance(60.0f),
    _collisionModels(collisionModels)
{
    _modelId = Eend::Entities::ModelBatch::insert(modelPath);
    Eend::Model& modelRef = Eend::Entities::ModelBatch::getRef(_modelId);
    modelRef.setScale(glm::vec3(1.0f));
    modelRef.setPosition(position);
}

Player::~Player() {
    Eend::Entities::ModelBatch::erase(_modelId);
}

void Player::setPosition(glm::vec3 position) {
    _strikeCollision.setPosition(glm::vec3(position.x, position.y + _strikeOffset, position.z));
    _hitBox.setPosition(glm::vec3(position.x, position.y, position.z));
    Eend::Model& modelRef = Eend::Entities::ModelBatch::getRef(_modelId);
    modelRef.setPosition(glm::vec3(position.x, position.y + _modelOffset, position.z));
}

void Player::setRadians(glm::vec2 rotation) { 
    Eend::Model& modelRef = Eend::Entities::ModelBatch::getRef(_modelId);
    modelRef.setRadians(rotation.x, rotation.y); 
}

void Player::update(const float dt) {
    Eend::Model& modelRef = Eend::Entities::ModelBatch::getRef(_modelId);
    for(int i = 0; i < 4; i++) {
        float speed = 20.000f;
        // move based on input and gravity
        _cameraRotation.x += Eend::InputManager::deltaMouseX / 100.0f;
        _cameraRotation.y += Eend::InputManager::deltaMouseY / 100.0f;

        // so that this number doesn't grow out of control and lose accuracy it loops at 2pi
        while (_cameraRotation.x > std::numbers::pi) {
            _cameraRotation.x -= 2 * std::numbers::pi;
        }
        while (_cameraRotation.x < std::numbers::pi) {
            _cameraRotation.x += 2 * std::numbers::pi;
        }

        // capping the camera height at the top of the sin wave
        if (_cameraRotation.y > std::numbers::pi * 0.5) {
            _cameraRotation.y = std::numbers::pi * 0.5;
        } else if (_cameraRotation.y < -(std::numbers::pi * 0.5)) {
            _cameraRotation.y = -(std::numbers::pi * 0.5);
        }
        
        if (_fallVelocity > -50.0f) {
            _fallVelocity -= 1.0f;
        }
        
        if (Eendgine::InputManager::upPress) {
            // TODO fix adjustment and find out where forward actually is
            modelRef.setRadians(_cameraRotation.x + (std::numbers::pi / 2), 0.0f);
            _position.x -= (speed * cos(_cameraRotation.x)) * dt;
            _position.z -= (speed * sin(_cameraRotation.x)) * dt;
        }
        if (Eendgine::InputManager::downPress) {
            _position.x += (speed * cos(_cameraRotation.x)) * dt;
            _position.z += (speed * sin(_cameraRotation.x)) * dt;
        }
        if (Eendgine::InputManager::leftPress) {
            _position.x -= (speed * sin(_cameraRotation.x)) * dt;
            _position.z += (speed * cos(_cameraRotation.x)) * dt;
        }
        if (Eendgine::InputManager::rightPress) {
            _position.x += (speed * sin(_cameraRotation.x)) * dt;
            _position.z -= (speed * cos(_cameraRotation.x)) * dt;
        }
        if (Eendgine::InputManager::spacePress) {
            _fallVelocity = 25;
            _strike = true;
        } else {
            _strike = false;
        }
        
        _position.y += _fallVelocity * dt;
        // adjust for collisions
        _hitBox.setPosition(glm::vec3(_position.x, _position.y, _position.z));
        // DEBUG
        
        auto begin_col = std::chrono::high_resolution_clock::now();
        
        Eend::CollisionResults colResults = Eend::adjustToCollision(_hitBox, _collisionModels);
        
        auto end_col = std::chrono::high_resolution_clock::now();
        static int avg_iter = 0;
        static std::array<int, 1000> avg_array;
        avg_array[avg_iter] = std::chrono::duration_cast<std::chrono::nanoseconds>(end_col - begin_col).count();  
        avg_iter++;
        if (avg_iter == avg_array.size()) avg_iter = 0;

        if (auto floorHeight = colResults.floor) {
            _position.y += *floorHeight;
            if(_fallVelocity < 0) _fallVelocity = 0;
        } else if (auto ceilingHeight = colResults.ceiling) {
            _position.y = *ceilingHeight;
            if(_fallVelocity > 0) _fallVelocity = 0;
        } else {
        }
        if (auto wallOffset = colResults.wall) {
            _position.x += wallOffset->x;
            _position.z += wallOffset->z;
        }
        setPosition(glm::vec3(_position.x, _position.y, _position.z));
    }  
    _camera.setTarget(_position.x, _position.y + 4, _position.z);
    _camera.setPosition(
            _position.x + (_cameraDistance * cos(_cameraRotation.x)), 
            _position.y + (_cameraDistance * sin(_cameraRotation.y)), 
            _position.z + (_cameraDistance * sin(_cameraRotation.x)));
}
