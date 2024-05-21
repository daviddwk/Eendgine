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
    template<class E>
    struct Comparator {
        bool operator()(E* entity1, E* entity2) const {
            return entity1->getTexture() > entity2->getTexture();
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

    template<class E>
    class ModelBatch {
        public:
            void insertModel(E* entity) {
                _entities.insert(entity);
            }

            void eraseModel(E* entity) {
                _entities.erase(entity);
            }
            
            void draw(ShaderProgram &shader) {
                shader.use();
                glActiveTexture(GL_TEXTURE0);
                std::string texName = "texture_diffuse";
                glUniform1i(glGetUniformLocation(
                            shader.getProgramID(), texName.c_str()), 0);
                unsigned int lastTexture = 0;
                unsigned int thisTexture = 0; 
                for (auto entity : _entities) {
                    thisTexture = entity->getTexture(); 
                    if (lastTexture != thisTexture) {
                        glBindTexture(GL_TEXTURE_2D, thisTexture);
                    }
                    lastTexture = thisTexture;
                    entity->draw(shader.getProgramID(), false);
                }
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        private:
            std::set<E*, Comparator<E>> _entities;
                    
            };
}
