#pragma once

#include <eendgine/model.hpp>
#include <eendgine/sprite.hpp>
#include <eendgine/drawBatch.hpp>
#include "shaders.hpp"

namespace Eend = Eendgine;

class DrawBatches {
    public:
        DrawBatches() { };

        void insert(Eend::StaticModel* model) { _models.insert(model); };
        void insert(Eend::AnimatedModel* model) { _animations.insert(model); };
        void insert(Eend::Sprite2D* sprite) { _sprites.insert(sprite); };
        void insert(Eend::Sprite3D* sprite) { _facingPlanes.insert(sprite); };

        void remove(Eend::StaticModel* model) { _models.erase(model); };
        void remove(Eend::AnimatedModel* model) { _animations.erase(model); };
        void remove(Eend::Sprite2D* sprite) { _sprites.erase(sprite); };
        void remove(Eend::Sprite3D* sprite) { _facingPlanes.erase(sprite); };

        void draw(Shaders&);
    private:
        Eend::DrawBatch<Eend::StaticModel> _models;
        Eend::DrawBatch<Eend::AnimatedModel> _animations;
        Eend::DrawBatch<Eend::Sprite2D> _sprites;
        Eend::DrawBatch<Eend::Sprite3D> _facingPlanes;
};
