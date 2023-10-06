#pragma once

#include <eendgine/sprite.hpp>
#include <eendgine/texture.hpp>
#include <eendgine/inputManager.hpp>

#include <vector>

class Player {
    public:
        void init(float x, float y, float z, float w, float h, Eendgine::Texture texture);
        void init(float x, float y, float z, float w, float h, std::vector<Eendgine::Texture> texture);
        void update(std::vector<Eendgine::Sprite *> collisionSprites);
        void render(Eendgine::ShaderProgram *shader, Eendgine::Camera2D *camera);
    private:
        // bool colliding(Eendgine::Sprite sprite1, Eendgine::Sprite sprite2);
        Eendgine::Sprite _sprite; 
        struct Velocity {
            float x = 0;
            float y = 0;
        }_velocity;
        bool _onGround = false;
        bool _groundJump = false;
        bool _releasedAfterJump = false; 
};
