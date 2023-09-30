#include "player.hpp"

#include <iostream>

void Player::init(float x, float y, float w, float h, Eendgine::Texture texture){
    _sprite.init(x, y, w, h, texture);
}

void Player::update(Eendgine::InputManager inMan, std::vector<Eendgine::Sprite> collisionSprites){
    float speed = 2.0f;

    if(inMan.leftPress && inMan.rightPress){
        _velocity.x = 0.0f;
    } else if(inMan.leftPress) {
        _velocity.x = -speed;
    } else if(inMan.rightPress) {
        _velocity.x = speed;
    } else {
        _velocity.x = 0.0f;
    }

    _velocity.y -= speed * 0.01f;

    if(inMan.spacePress){
        _velocity.y = speed;
    }

    _sprite.x += _velocity.x;
    _sprite.y += _velocity.y;
    
    int numSprites = collisionSprites.size();
    for(int i= 0; i < numSprites; i++){
        float xDistance = _sprite.x - collisionSprites[i].x;
        float xCollisionDepth = ((_sprite.w / 2) + (collisionSprites[i].w / 2)) - abs(xDistance);
        float yDistance = _sprite.y - collisionSprites[i].y;
        float yCollisionDepth = ((_sprite.h / 2) + (collisionSprites[i].h / 2)) - abs(yDistance);
        std::cout << "x dis:col" << xDistance << ' ' << xCollisionDepth << std::endl;
        std::cout << "y dis:col" << yDistance << ' ' << yCollisionDepth << std::endl;
        if ((xCollisionDepth > 0) && (yCollisionDepth > 0)){
            std::cout << "coliding" << std::endl;
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
                        _velocity.y = 0;
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
