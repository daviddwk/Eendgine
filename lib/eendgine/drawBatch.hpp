#pragma once
#include "model.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "sprite.hpp"

#include <set>
#include <functional>

namespace Eendgine {
    template<class E>
    static bool textureCompare(E* entity1, E* entity2) {
        return entity1->getTexture() > entity2->getTexture();
    }

    template<class E>
    class DrawBatch {
        public:
            //assuming that you don't put two of the same in here, but not checking
            void insert(E* entity) {
                _entities.push_back(entity);
            }

            void erase(E* entity) {
                auto iter = std::find(_entities.begin(), _entities.end(), entity);
                _entities.erase(iter);
            }

            void sort() {
                std::sort(_entities.begin(), _entities.end(), textureCompare<E>);
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
                    entity->draw(shader.getProgramID());
                }
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        private:
            // this probably shouldn't be a vector of pointers, 
            // but I'll get around to making a real ECS later
            //
            // vector so I can control when it sorts
            std::vector<E*> _entities;
    };
}
