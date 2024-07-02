#pragma once

#include "model.hpp"
#include "sprite.hpp"
#include "entityBatch.hpp"
#include "camera.hpp"
#include "shaders.hpp"

#include <filesystem>


namespace Eendgine {
    using ModelId = unsigned int;
    using AnimationId = unsigned int;
    using BillboardId = unsigned int;
    using PanelId = unsigned int;
    class Entities {
        public:
            class ModelBatch {
                public:
                    static ModelId insert(std::string modelPath) { 
                        return _models.insert(modelPath); 
                    };
                    static void erase(ModelId id) { _models.erase(id); };
                    static Model& getRef(ModelId id) { return _models.getRef(id); }
            };
            class AnimationBatch {
                public:
                    static AnimationId insert(std::filesystem::path modelsDir) { 
                        return _animations.insert(modelsDir); 
                    };
                    static void erase(AnimationId id) { _animations.erase(id); };
                    static Animation& getRef(AnimationId id) { return _animations.getRef(id); }
            };
            class BillboardBatch {
                public:
                    static BillboardId insert(std::vector<std::string> texturePaths) { 
                        return _billboards.insert(texturePaths); 
                    };
                    static void erase(BillboardId id) { _billboards.erase(id); };
                    static Sprite& getRef(BillboardId id) { return _billboards.getRef(id); }
            };
            class PanelBatch {
                public:
                    static PanelId insert(std::vector<std::string> texturePaths) { 
                        return _panels.insert(texturePaths); 
                    };
                    static void erase(PanelId id) { _panels.erase(id); };
                    static Sprite& getRef(PanelId id) { return _panels.getRef(id); }
            };
            static void draw(Shaders &shaders, Camera2D &hudCamera, Camera3D &sceneCamera);
        private:
            inline static DrawBatch<Model> _models;
            inline static DrawBatch<Animation> _animations;
            inline static DrawBatch<Sprite> _billboards;
            inline static DrawBatch<Sprite> _panels;
    };
}
