#pragma once

#include <eendgine/sprite.hpp>
#include <eendgine/camera.hpp>
#include <eendgine/textureCache.hpp>
#include "drawBatches.hpp"


namespace Eend = Eendgine;

class Ball {
    public:
        Ball(std::string texturePath, glm::vec3 position, 
                Eend::TextureCache& textureCache, Eend::Camera3D& camera, DrawBatches& drawBatches);
        Ball();
        ~Ball();
        void setPosition(glm::vec3 position);
        glm::vec3 getPosition() { return _position; };
        void update(float dt);
    private:
        Eend::Sprite3D _sprite;
        
        Eend::Camera3D& _camera;
        DrawBatches& _drawBatches;

        glm::vec3 _position;
        glm::vec3 _destination; //x, z
        
        const float _halfCourtWidth = 35.0f;
        const float _halfCourtLength = 55.0f;
        const float _peakHeight = 30.0f;
        const float _speedMultiplier = 100.0f;
};
