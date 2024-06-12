#pragma once

#include "model.hpp"
#include "sprite.hpp"
#include "entityBatch.hpp"
#include "camera.hpp"
#include "shaders.hpp"

using ModelId = unsigned int;
using AnimationId = unsigned int;
using BillboardId = unsigned int;
using SpriteId = unsigned int;

namespace Eendgine {
    class EntityBatches {
        public:
            static ModelId insertModel(std::string modelPath) { 
                return _models.insert(modelPath); 
            };
            static AnimationId insertAnimation(std::vector<std::string> modelPaths) { 
                return _animations.insert(modelPaths); 
            };
            static BillboardId insertBillboard(std::vector<std::string> texturePaths) { 
                return _billboards.insert(texturePaths); 
            };
            static SpriteId insertSprite(std::vector<std::string> texturePaths) { 
                return _sprites.insert(texturePaths); 
            };

            static void eraseModel(ModelId id) { _models.erase(id); };
            static void eraseAnimation(AnimationId id) { _animations.erase(id); };
            static void eraseBillboard(BillboardId id) { _billboards.erase(id); };
            static void eraseSprite(SpriteId id) { _sprites.erase(id); };

            static StaticModel& getRefModel(ModelId id) { return _models.getRef(id); }
            static AnimatedModel& getRefAnimation(AnimationId id) { return _animations.getRef(id); }
            static Sprite& getRefBillboard(BillboardId id) { return _billboards.getRef(id); }
            static Sprite& getRefSprite(SpriteId id) { return _sprites.getRef(id); }

            static void draw(Shaders &shaders, Camera2D &hudCamera, Camera3D &sceneCamera);
        private:
            inline static EntityBatch<StaticModel> _models;
            inline static EntityBatch<AnimatedModel> _animations;
            inline static EntityBatch<Sprite> _billboards;
            inline static EntityBatch<Sprite> _sprites;
    };
}
