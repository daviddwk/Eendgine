#pragma once
#include "model.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "sprite.hpp"

#include <set>
#include <functional>

namespace Eendgine {
    struct SpriteComparator {
        bool operator()(Sprite* s1, Sprite* s2) const {
            return s1->getTexture() > s2->getTexture();
        }
    };
    struct ModelComparator {
        bool operator()(Model* m1, Model* m2) const {
            return m1->getTexture() > m2->getTexture();
        }
    };
    class SpriteBatch {
        public:
            SpriteBatch();
            void insertSprite(Sprite* sprite);
            void eraseSprite(Sprite* sprite);
            void draw(ShaderProgram &shader, Camera3D &camera);
            void draw(ShaderProgram &shader, Camera2D &camera);

        private:
            std::set<Sprite*, SpriteComparator> _sprites;
    };
    class ModelBatch {
        public:
            ModelBatch();
            void insertModel(Model* model);
            void eraseModel(Model* model);
            void draw(ShaderProgram &shader, Camera3D &camera);

        private:
            std::set<Model*, ModelComparator> _models;
    };
}
