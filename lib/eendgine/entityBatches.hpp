#pragma once

#include "model.hpp"
#include "sprite.hpp"
#include "entityBatch.hpp"
#include "camera.hpp"
#include "shaders.hpp"


namespace Eendgine {
    using ModelId = unsigned int;
    using AnimationId = unsigned int;
    using BillboardId = unsigned int;
    using PanelId = unsigned int;
    class EntityBatches {
        public:
            class Model {
                public:
                    static ModelId insert(std::string modelPath) { 
                        return _models.insert(modelPath); 
                    };
                    static void erase(ModelId id) { _models.erase(id); };
                    static StaticModel* getRef(ModelId id) { return _models.getRef(id); }
            };
            class Animation {
                public:
                    static AnimationId insert(std::vector<std::string> modelPaths) { 
                        return _animations.insert(modelPaths); 
                    };
                    static void erase(AnimationId id) { _animations.erase(id); };
                    static AnimatedModel* getRef(AnimationId id) { return _animations.getRef(id); }
            };
            class Billboard {
                public:
                    static BillboardId insert(std::vector<std::string> texturePaths) { 
                        return _billboards.insert(texturePaths); 
                    };
                    static void erase(BillboardId id) { _billboards.erase(id); };
                    static Sprite* getRef(BillboardId id) { return _billboards.getRef(id); }
            };
            class Icon {
                public:
                    static PanelId insert(std::vector<std::string> texturePaths) { 
                        return _panels.insert(texturePaths); 
                    };
                    static void erase(PanelId id) { _panels.erase(id); };
                    static Sprite* getRef(PanelId id) { return _panels.getRef(id); }
            };
            static void draw(Shaders &shaders, Camera2D &hudCamera, Camera3D &sceneCamera);
        private:
            inline static EntityBatch<StaticModel> _models;
            inline static EntityBatch<AnimatedModel> _animations;
            inline static EntityBatch<Sprite> _billboards;
            inline static EntityBatch<Sprite> _panels;
    };
}
