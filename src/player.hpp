#include <eendgine/model.hpp>
#include <eendgine/collisionGeometry.hpp>
#include "drawBatches.hpp"

namespace Eend = Eendgine;

class Player {
    public:
        Player(DrawBatches& drawBatches, std::vector<Eend::CollisionModel*>& collisionModels,
                glm::vec3 position, 
                std::string modelPath, Eend::TextureCache& textureCache, Eend::Camera3D& camera, 
                float hitHeight, float hitRadius, float hitOffset, 
                float strikeRadius, float strikeOffset);
        ~Player();
        void update(float dt);

        void setPosition(glm::vec3 position) {
            _strikeZone.setPosition(position + _strikeOffset);
            _hitBox.setPosition(position + _hitBoxOffset);
            _model.setPosition(position);
        };
        void setRadians(glm::vec2 rotation) {
            _model.setRadians(rotation.x, rotation.y);
        }
        /*
        void setAnimation(float scale) {
            _model.setAnim(scale);
        };
        */
    private:
        Eend::CollisionSphere _strikeZone;
        Eend::CollisionCylinder _hitBox;
        Eend::StaticModel _model;
        
        Eend::Camera3D& _camera;
        
        glm::vec2 _cameraRotation;
        glm::vec3 _position;
        float _strikeOffset;
        float _hitBoxOffset;
        float _fallVelocity;
        float _cameraDistance;
        std::vector<Eend::CollisionModel*>& _collisionModels;
        DrawBatches& _drawBatches;
};
