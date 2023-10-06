#include "player.hpp"
#include <eendgine/frameLimiter.hpp>
#include <eendgine/inputManager.hpp>

#include <vector>

namespace Eend = Eendgine;

void Player::init(float x, float y, float z, float w, float h, Eend::Texture texture){
    _sprite.init(x, y, z, w, h, texture);
}

void Player::init(float x, float y, float z, float w, float h, std::vector<Eend::Texture> textures){
    _sprite.init(x, y, z, w, h, textures);
}

void Player::update(std::vector<Eend::Sprite *> collisionSprites){
    
    float dt = Eend::FrameLimiter::deltaTime;
    float speed = 150.0f;
    float fallSpeed = 400.0f;
    float jumpSpeed = 300.0f;
    float airSpeed = 200.0f;
    
    if(_onGround) {
        if(Eend::InputManager::leftPress && Eend::InputManager::rightPress){
            _velocity.x = 0.0f;
        } else if(Eend::InputManager::leftPress) {
            _velocity.x = -speed;
        } else if(Eend::InputManager::rightPress) {
            _velocity.x = speed;
        } else {
            _velocity.x = 0.0f;
        }
    } else {
        if(Eend::InputManager::leftPress && Eend::InputManager::rightPress){

        } else if(Eend::InputManager::leftPress && !(_velocity.x <= -speed)) {
            _velocity.x -= airSpeed * dt;
        } else if(Eend::InputManager::rightPress && !(_velocity.x >= speed)) {
            _velocity.x += airSpeed * dt;
        }
    }

    if(_groundJump == true){
        if(_releasedAfterJump == true && Eend::InputManager::spacePress){
            _velocity.y = jumpSpeed;
            _groundJump = false;
            _releasedAfterJump = false;
            _sprite.setTexture(0);
        } else if (_releasedAfterJump == false && !Eend::InputManager::spacePress) {
            _releasedAfterJump = true;
        }
    }

    _velocity.y -= fallSpeed * dt;


    _sprite.x += _velocity.x * dt;
    _sprite.y += _velocity.y * dt;
    
    int numSprites = collisionSprites.size();
    _onGround = false;
    for(int i= 0; i < numSprites; i++){
        float xDistance = _sprite.x - collisionSprites[i]->x;
        float xCollisionDepth = ((_sprite.w / 2) + (collisionSprites[i]->w / 2)) - abs(xDistance);
        float yDistance = _sprite.y - collisionSprites[i]->y;
        float yCollisionDepth = ((_sprite.h / 2) + (collisionSprites[i]->h / 2)) - abs(yDistance);

        if ((xCollisionDepth > 0) && (yCollisionDepth > 0)){
            // distance of centers of sprites
            if(xCollisionDepth > 0 && xCollisionDepth < yCollisionDepth) {
                // player to the left of coliding object
                if(xDistance > 0){
                    // test if this if is nessary
                    if(_velocity.x < 0) {
                        _velocity.x = 0;
                        _sprite.x += xCollisionDepth;
                    }
                // player to the right of coliding object
                } else {
                    if(_velocity.x > 0) {
                        _velocity.x = 0;
                        _sprite.x -= xCollisionDepth;
                    }
                }
            } else {
                // player above of coliding object
                _onGround = true;
                if(yDistance > 0){
                    // test if this if is nessary
                    if(_velocity.y < 0) {
                        if(Eend::InputManager::spacePress && _velocity.y <= 0.0f){
                            _velocity.y = jumpSpeed;
                            _groundJump = true;
                            _sprite.setTexture(1);
                        } else {
                            _velocity.y = 0;
                            _groundJump = false;
                        }
                        _sprite.y += yCollisionDepth;
                    }
                // player below coliding object
                } else {
                    if(_velocity.y > 0) {
                        _velocity.y = 0;
                        _sprite.y -= yCollisionDepth;
                    }
                }
            }
        }
    }

    std::cout<< _onGround << std::endl;
}

void Player::render(Eend::ShaderProgram *shader, Eend::Camera2D *camera){
    _sprite.render(shader, camera);
}
