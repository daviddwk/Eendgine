#include "player.hpp"

void Player::init(float x, float y, float w, float h, Eendgine::Texture texture){
    _sprite.init(x, y, w, h, texture);
}

void Player::update(Eendgine::InputManager *inMan, std::vector<Eendgine::Sprite *> collisionSprites){
    float speed = 8.0f;
    float jumpSpeed = 10.0f;

    if(inMan->leftPress && inMan->rightPress){
        _velocity.x = 0.0f;
    } else if(inMan->leftPress) {
        _velocity.x = -speed;
    } else if(inMan->rightPress) {
        _velocity.x = speed;
    } else {
        _velocity.x = 0.0f;
    }

    if(_groundJump == true){
        if(_releasedAfterJump == true && inMan->spacePress){
            _velocity.y = jumpSpeed;
            _groundJump = false;
            _releasedAfterJump = false;
        } else if (_releasedAfterJump == false && !inMan->spacePress) {
            _releasedAfterJump = true;
        }
    }

    _velocity.y -= speed * 0.03f;


    _sprite.x += _velocity.x;
    _sprite.y += _velocity.y;
    
    int numSprites = collisionSprites.size();
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
                if(yDistance > 0){
                    // test if this if is nessary
                    if(_velocity.y < 0) {
                        if(inMan->spacePress && _velocity.y <= 0.0f){
                            _velocity.y = jumpSpeed;
                            _groundJump = true;
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
}

void Player::render(Eendgine::ShaderProgram *shader, Eendgine::Camera2D *camera){
    _sprite.render(shader, camera);
}
