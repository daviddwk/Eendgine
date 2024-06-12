#pragma once

#include <eendgine/model.hpp>
#include <eendgine/sprite.hpp>
#include <eendgine/drawBatch.hpp>
#include <eendgine/shaders.hpp>

namespace Eend = Eendgine;

class DrawBatches {
    public:
        DrawBatches() { };

        void insertModel(Eend::StaticModel* model) { _models.insert(model); };
        void insertAnimation(Eend::AnimatedModel* model) { _animations.insert(model); };
        void insertSprite(Eend::Sprite* sprite) { _sprites.insert(sprite); };
        void insertFacing(Eend::Sprite* sprite) { _facingPlanes.insert(sprite); };

        void removeModel(Eend::StaticModel* model) { _models.erase(model); };
        void removeAnimation(Eend::AnimatedModel* model) { _animations.erase(model); };
        void removeSprite(Eend::Sprite* sprite) { _sprites.erase(sprite); };
        void removeFacing(Eend::Sprite* sprite) { _facingPlanes.erase(sprite); };

        void draw(Eend::Shaders& shaders, Eend::Camera2D &hudCamera, Eend::Camera3D &sceneCamera);
        void sort();
    private:
        Eend::DrawBatch<Eend::StaticModel> _models;
        Eend::DrawBatch<Eend::AnimatedModel> _animations;
        Eend::DrawBatch<Eend::Sprite> _sprites;
        Eend::DrawBatch<Eend::Sprite> _facingPlanes;
};
